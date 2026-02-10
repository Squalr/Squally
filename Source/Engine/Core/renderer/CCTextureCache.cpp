/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "renderer/CCTextureCache.h"

#include <errno.h>
#include <stack>
#include <cctype>
#include <list>

#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCScheduler.h"
#include "base/ccUTF8.h"
#include "base/ccUtils.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTexture2D.h"

using namespace std;

NS_CC_BEGIN

std::string TextureCache::s_etc1AlphaFileSuffix = "@alpha";

TextureCache::TextureCache()
: _loadingThread(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
{
}

TextureCache::~TextureCache()
{
    CCLOGINFO("deallocing TextureCache: %p", this);

    for (auto& texture : _textures)
        texture.second->release();

    CC_SAFE_DELETE(_loadingThread);
}

std::string TextureCache::getDescription() const
{
    return StringUtils::format("<TextureCache | Number of textures = %d>", static_cast<int>(_textures.size()));
}

struct TextureCache::AsyncStruct
{
public:
    AsyncStruct
    ( const std::string& fn,const std::function<void(Texture2D*)>& f,
      const std::string& key )
      : filename(fn), callback(f),callbackKey( key ),
        pixelFormat(Texture2D::getDefaultAlphaPixelFormat()),
        loadSuccess(false)
    {}

    std::string filename;
    std::function<void(Texture2D*)> callback;
    std::string callbackKey;
    Image image;
    Image imageAlpha;
    Texture2D::PixelFormat pixelFormat;
    bool loadSuccess;
};

void TextureCache::cacheImageAsync(const std::string &filepath)
{
    addImageAsync(filepath, nullptr, filepath);
}

/**
 The addImageAsync logic follow the steps:
 - find the image has been add or not, if not add an AsyncStruct to _requestQueue  (GL thread)
 - get AsyncStruct from _requestQueue, load res and fill image data to AsyncStruct.image, then add AsyncStruct to _responseQueue (Load thread)
 - on schedule callback, get AsyncStruct from _responseQueue, convert image to texture, then delete AsyncStruct (GL thread)

 the Critical Area include these members:
 - _requestQueue: locked by _requestMutex
 - _responseQueue: locked by _responseMutex

 the object's life time:
 - AsyncStruct: construct and destruct in GL thread
 - image data: new in Load thread, delete in GL thread(by Image instance)

 Note:
 - all AsyncStruct referenced in _asyncStructQueue, for unbind function use.

 How to deal add image many times?
 - At first, this situation is abnormal, we only ensure the logic is correct.
 - If the image has been loaded, the after load image call will return immediately.
 - If the image request is in queue already, there will be more than one request in queue,
 - In addImageAsyncCallback, will deduplicate the request to ensure only create one texture.

 Does process all response in addImageAsyncCallback consume more time?
 - Convert image to texture faster than load image from disk, so this isn't a
 problem.

 Call unbindImageAsync(path) to prevent the call to the callback when the
 texture is loaded.
 */
void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback)
{
    addImageAsync(path, callback, path);
}

/**
 The addImageAsync logic follow the steps:
 - find the image has been add or not, if not add an AsyncStruct to _requestQueue  (GL thread)
 - get AsyncStruct from _requestQueue, load res and fill image data to AsyncStruct.image, then add AsyncStruct to _responseQueue (Load thread)
 - on schedule callback, get AsyncStruct from _responseQueue, convert image to texture, then delete AsyncStruct (GL thread)
 
 the Critical Area include these members:
 - _requestQueue: locked by _requestMutex
 - _responseQueue: locked by _responseMutex
 
 the object's life time:
 - AsyncStruct: construct and destruct in GL thread
 - image data: new in Load thread, delete in GL thread(by Image instance)
 
 Note:
 - all AsyncStruct referenced in _asyncStructQueue, for unbind function use.
 
 How to deal add image many times?
 - At first, this situation is abnormal, we only ensure the logic is correct.
 - If the image has been loaded, the after load image call will return immediately.
 - If the image request is in queue already, there will be more than one request in queue,
 - In addImageAsyncCallback, will deduplicate the request to ensure only create one texture.
 
 Does process all response in addImageAsyncCallback consume more time?
 - Convert image to texture faster than load image from disk, so this isn't a
 problem.

 The callbackKey allows to unbind the callback in cases where the loading of
 path is requested by several sources simultaneously. Each source can then
 unbind the callback independently as needed whilst a call to
 unbindImageAsync(path) would be ambiguous.
 */
void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback, const std::string& callbackKey)
{
    Texture2D *texture = nullptr;

    auto it = _textures.find(path);
    
    if (it != _textures.end())
    {
        texture = it->second;
    }

    if (texture != nullptr)
    {
        if (callback != nullptr)
        {
            callback(texture);
        }

        return;
    }

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);

    // lazy init
    if (_loadingThread == nullptr)
    {
        // create a new thread to load images
        _needQuit = false;
        _loadingThread = new (std::nothrow) std::thread(&TextureCache::loadImage, this);
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(TextureCache::addImageAsyncCallBack, this), this, "ADD_IMG");
    }

    ++_asyncRefCount;

    // generate async struct
    AsyncStruct *data = new (std::nothrow) AsyncStruct(fullpath, callback, callbackKey);
    
    // add async struct into queue
    _asyncStructQueue.push_back(data);
    std::unique_lock<std::mutex> ul(_requestMutex);
    _requestQueue.push_back(data);
    _sleepCondition.notify_one();
}

void TextureCache::unbindImageAsync(const std::string& callbackKey)
{
    if (_asyncStructQueue.empty())
    {
        return;
    }

    for (auto& asyncStruct : _asyncStructQueue)
    {
        if (asyncStruct->callbackKey == callbackKey)
        {
            asyncStruct->callback = nullptr;
        }
    }
}

void TextureCache::unbindAllImageAsync()
{
    if (_asyncStructQueue.empty())
    {
        return;

    }
    for (auto& asyncStruct : _asyncStructQueue)
    {
        asyncStruct->callback = nullptr;
    }
}

void TextureCache::loadImage()
{
    AsyncStruct *asyncStruct = nullptr;
    while (!_needQuit)
    {
        std::unique_lock<std::mutex> ul(_requestMutex);
        // pop an AsyncStruct from request queue
        if (_requestQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _requestQueue.front();
            _requestQueue.pop_front();
        }

        if (nullptr == asyncStruct) {
            if (_needQuit) {
                break;
            }
            _sleepCondition.wait(ul);
            continue;
        }
        ul.unlock();

        // load image
        asyncStruct->loadSuccess = asyncStruct->image.initWithImageFileThreadSafe(asyncStruct->filename);
        
        // push the asyncStruct to response queue
        _responseMutex.lock();
        _responseQueue.push_back(asyncStruct);
        _responseMutex.unlock();
    }
}

void TextureCache::addImageAsyncCallBack(float /*dt*/)
{
    Texture2D *texture = nullptr;
    AsyncStruct *asyncStruct = nullptr;
    while (true)
    {
        // pop an AsyncStruct from response queue
        _responseMutex.lock();
        if (_responseQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _responseQueue.front();
            _responseQueue.pop_front();

            // the asyncStruct's sequence order in _asyncStructQueue must equal to the order in _responseQueue
            CC_ASSERT(asyncStruct == _asyncStructQueue.front());
            _asyncStructQueue.pop_front();
        }
        _responseMutex.unlock();

        if (nullptr == asyncStruct) {
            break;
        }

        // check the image has been convert to texture or not
        auto it = _textures.find(asyncStruct->filename);
        if (it != _textures.end())
        {
            texture = it->second;
        }
        else
        {
            // convert image to texture
            if (asyncStruct->loadSuccess)
            {
                Image* image = &(asyncStruct->image);
                // generate texture in render thread
                texture = new (std::nothrow) Texture2D();

                texture->initWithImage(image, asyncStruct->pixelFormat);
                // cache the texture. retain it, since it is added in the map
                _textures.emplace(asyncStruct->filename, texture);
                texture->retain();

                texture->autorelease();
            }
            else {
                texture = nullptr;
                CCLOG("cocos2d: failed to call TextureCache::addImageAsync(%s)", asyncStruct->filename.c_str());
            }
        }

        // call callback function
        if (asyncStruct->callback)
        {
            (asyncStruct->callback)(texture);
        }

        // release the asyncStruct
        delete asyncStruct;
        --_asyncRefCount;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->unschedule("ADD_IMG", this);
    }
}

Texture2D * TextureCache::addImage(const std::string& path)
{
    Texture2D * texture = nullptr;
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread
    
    auto it = _textures.find(path);

    if (it != _textures.end())
    {
        return it->second;
    }

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);

    if (fullpath.size() == 0)
    {
        return nullptr;
    }
    
    it = _textures.find(fullpath);

    if (it != _textures.end())
    {
        return it->second;
    }
    
    Image* image = nullptr;

    if (!texture)
    {
        // all images are handled by UIImage
        do
        {
            image = new (std::nothrow) Image();
            CC_BREAK_IF(nullptr == image);

            bool bRet = image->initWithImageFile(fullpath);
            CC_BREAK_IF(!bRet);

            texture = new (std::nothrow) Texture2D();

            if (texture && texture->initWithImage(image))
            {
                // texture already retained, no need to re-retain it
                _textures.emplace(path, texture);
            }
            else
            {
                CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", path.c_str());
                CC_SAFE_RELEASE(texture);
                texture = nullptr;
            }
        } while (0);
    }

    CC_SAFE_RELEASE(image);

    return texture;
}

Texture2D* TextureCache::addImage(Image *image, const std::string &key)
{
    CCASSERT(image != nullptr, "TextureCache: image MUST not be nil");
    CCASSERT(image->getData() != nullptr, "TextureCache: image MUST not be nil");

    Texture2D * texture = nullptr;

    do
    {
        auto it = _textures.find(key);

        if (it != _textures.end())
        {
            texture = it->second;
            break;
        }

        texture = new (std::nothrow) Texture2D();

        if (texture)
        {
            if (texture->initWithImage(image))
            {
                _textures.emplace(key, texture);
            }
            else
            {
                CC_SAFE_RELEASE(texture);
                texture = nullptr;
                CCLOG("cocos2d: initWithImage failed!");
            }
        }
        else
        {
            CCLOG("cocos2d: Allocating memory for Texture2D failed!");
        }

    } while (0);

    return texture;
}

bool TextureCache::reloadTexture(const std::string& fileName)
{
    Texture2D * texture = nullptr;
    Image * image = nullptr;

    auto it = _textures.find(fileName);

    if (it != _textures.end())
    {
        texture = it->second;
    }

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(fileName);
    
    if (fullpath.size() == 0)
    {
        return false;
    }

    bool ret = false;
    if (!texture)
    {
        texture = this->addImage(fullpath);
        ret = (texture != nullptr);
    }
    else
    {
        do {
            image = new (std::nothrow) Image();
            CC_BREAK_IF(nullptr == image);

            bool bRet = image->initWithImageFile(fullpath);
            CC_BREAK_IF(!bRet);

            ret = texture->initWithImage(image);
        } while (0);
    }

    CC_SAFE_RELEASE(image);

    return ret;
}

// TextureCache - Remove

void TextureCache::removeAllTextures()
{
    for (auto& texture : _textures) {
        texture.second->release();
    }
    _textures.clear();
}

void TextureCache::removeUnusedTextures()
{
    for (auto it = _textures.cbegin(); it != _textures.cend(); /* nothing */) {
        Texture2D *tex = it->second;
        if (tex->getReferenceCount() == 1) {
            CCLOG("cocos2d: TextureCache: removing unused texture: %s", it->first.c_str());

            tex->release();
            it = _textures.erase(it);
        }
        else {
            ++it;
        }

    }
}

void TextureCache::removeTexture(Texture2D* texture)
{
    if (!texture)
    {
        return;
    }

    for (auto it = _textures.cbegin(); it != _textures.cend(); /* nothing */) {
        if (it->second == texture) {
            it->second->release();
            it = _textures.erase(it);
            break;
        }
        else
            ++it;
    }
}

void TextureCache::removeTextureForKey(const std::string &textureKeyName)
{
    std::string key = textureKeyName;
    auto it = _textures.find(key);

    if (it == _textures.end())
    {
        key = FileUtils::getInstance()->fullPathForFilename(textureKeyName);
        it = _textures.find(key);
    }

    if (it != _textures.end())
    {
        it->second->release();
        _textures.erase(it);
    }
}

Texture2D* TextureCache::getTextureForKey(const std::string &textureKeyName) const
{
    std::string key = textureKeyName;
    auto it = _textures.find(key);

    if (it == _textures.end())
    {
        key = FileUtils::getInstance()->fullPathForFilename(textureKeyName);
        it = _textures.find(key);
    }

    if (it != _textures.end())
    {
        return it->second;
    }

    return nullptr;
}

std::string TextureCache::getTextureFilePath(cocos2d::Texture2D* texture) const
{
    for (auto& item : _textures)
    {
        if (item.second == texture)
        {
            return item.first;
            break;
        }
    }
    return "";
}

void TextureCache::waitForQuit()
{
    // notify sub thread to quick
    std::unique_lock<std::mutex> ul(_requestMutex);
    _needQuit = true;
    _sleepCondition.notify_one();
    ul.unlock();
    if (_loadingThread) _loadingThread->join();
}

std::string TextureCache::getCachedTextureInfo() const
{
    std::string buffer;
    char buftmp[4096];

    unsigned int count = 0;
    unsigned int totalBytes = 0;

    for (auto& texture : _textures) {

        memset(buftmp, 0, sizeof(buftmp));


        Texture2D* tex = texture.second;
        unsigned int bpp = tex->getBitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        auto bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        snprintf(buftmp, sizeof(buftmp) - 1, "\"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB\n",
            texture.first.c_str(),
            (long)tex->getReferenceCount(),
            (long)tex->getName(),
            (long)tex->getPixelsWide(),
            (long)tex->getPixelsHigh(),
            (long)bpp,
            (long)bytes / 1024);

        buffer += buftmp;
    }

    snprintf(buftmp, sizeof(buftmp) - 1, "TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)\n", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
    buffer += buftmp;

    return buffer;
}

NS_CC_END
