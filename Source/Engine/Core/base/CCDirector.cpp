/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2013 cocos2d-x.org
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

#include "CCDirector.h"

#include <string>

#include "2d/CCActionManager.h"
#include "2d/CCCamera.h"
#include "2d/CCFontAtlasCache.h"
#include "2d/CCFontFreeType.h"
#include "base/CCAsyncTaskPool.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCConfiguration.h"
#include "base/CCConsole.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventCustom.h"
#include "base/ccMacros.h"
#include "base/CCScheduler.h"
#include "platform/CCApplication.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCFrameBuffer.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"

/**
 Position of the FPS
 
 Default: 0,0 (bottom-left corner)
 */
#ifndef CC_DIRECTOR_STATS_POSITION
#define CC_DIRECTOR_STATS_POSITION Director::getInstance()->getVisibleOrigin()
#endif // CC_DIRECTOR_STATS_POSITION

using namespace std;

NS_CC_BEGIN
// FIXME: it should be a Director ivar. Move it there once support for multiple directors is added

// singleton stuff
static Director *s_SharedDirector = nullptr;

#define kDefaultFPS        60  // 60 frames per second
extern const char* cocos2dVersion(void);

const std::string Director::EVENT_PROJECTION_CHANGED = "director_projection_changed";

Director* Director::getInstance()
{
    if (!s_SharedDirector)
    {
        s_SharedDirector = new (std::nothrow) Director;
        CCASSERT(s_SharedDirector, "FATAL: Not enough memory");
        s_SharedDirector->init();
    }

    return s_SharedDirector;
}

Director::Director()
: _isStatusLabelUpdated(true)
, _invalid(true)
, _deltaTimePassedByCaller(false)
, _actionManager(nullptr)
{
    const int MaxStackSize = 2048;

    _modelViewMatrixStack = std::vector<Mat4>(MaxStackSize);
    _matrixStackIndex = 0;
}

bool Director::init(void)
{
    setDefaultValues();

    // scenes
    _runningScene = nullptr;
    _nextScene = nullptr;

    _notificationNode = nullptr;

    _scenesStack.reserve(15);

    // FPS
    _accumDt = 0.0f;
    _frameRate = 0.0f;
    _totalFrames = 0;
    _lastUpdate = std::chrono::steady_clock::now();
    
    _secondsPerFrame = 1.0f;
    _frames = 0;

    // paused ?
    _paused = false;

    // purge ?
    _purgeDirectorInNextLoop = false;
    
    // restart ?
    _restartDirectorInNextLoop = false;
    
    // invalid ?
    _invalid = false;

    _winSizeInPoints = CSize::ZERO;

    _openGLView = nullptr;
    _defaultFBO = nullptr;
    
    _contentScaleFactor = 1.0f;

    // scheduler
    _scheduler = new (std::nothrow) Scheduler();
    // action manager
    _actionManager = new (std::nothrow) ActionManager();

    _scheduler->schedule(std::bind(&ActionManager::update,_actionManager, std::placeholders::_1), _actionManager, "ACTION_MGR_UPDATE");

    _eventDispatcher = new (std::nothrow) EventDispatcher();
    
    _eventProjectionChanged = new (std::nothrow) EventCustom(EVENT_PROJECTION_CHANGED);
    _eventProjectionChanged->setData(this);
    //init TextureCache
    initTextureCache();
    initMatrixStack();

    _renderer = new (std::nothrow) Renderer;
    RenderState::initialize();

    return true;
}

Director::~Director(void)
{
    CCLOGINFO("deallocing Director: %p", this);

    CC_SAFE_RELEASE(_runningScene);
    CC_SAFE_RELEASE(_notificationNode);
    CC_SAFE_RELEASE(_scheduler);
    CC_SAFE_RELEASE(_actionManager);
    CC_SAFE_DELETE(_defaultFBO);
    
    CC_SAFE_RELEASE(_eventProjectionChanged);

    delete _renderer;

    CC_SAFE_RELEASE(_eventDispatcher);
    
    Configuration::destroyInstance();

    s_SharedDirector = nullptr;
}

void Director::setDefaultValues(void)
{
    Configuration *conf = Configuration::getInstance();

    // default FPS
    double fps = conf->getValue("cocos2d.x.fps", Value(kDefaultFPS)).asDouble();
    _oldAnimationInterval = _animationInterval = 1.0 / fps;

    // GL projection
    std::string projection = conf->getValue("cocos2d.x.gl.projection", Value("3d")).asString();
    if (projection == "3d")
        _projection = Projection::_3D;
    else if (projection == "2d")
        _projection = Projection::_2D;
    else if (projection == "custom")
        _projection = Projection::CUSTOM;
    else
        CCASSERT(false, "Invalid projection value");

    // Default pixel format for PNG images with alpha
    std::string pixel_format = conf->getValue("cocos2d.x.texture.pixel_format_for_png", Value("rgba8888")).asString();
    if (pixel_format == "rgba8888")
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    else if(pixel_format == "rgba4444")
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    else if(pixel_format == "rgba5551")
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
}

void Director::setGLDefaultValues()
{
    // This method SHOULD be called only after openGLView_ was initialized
    CCASSERT(_openGLView, "opengl view should not be null");

    setAlphaBlending(true);
    setDepthTest(false);
    setProjection(_projection);
}

// Draw the Scene
void Director::drawScene()
{
    // calculate "global" dt
    calculateDeltaTime();
    
    if (_openGLView)
    {
        _openGLView->pollEvents();
    }

    //tick before glClear: issue #533
    if (! _paused)
    {
        _scheduler->update(_deltaTime);
    }

    _renderer->clear();
    cocos_experimental::FrameBuffer::clearAllFBOs();
    
    /* to avoid flickr, nextScene MUST be here: after tick and before draw.
     * FIXME: Which bug is this one. It seems that it can't be reproduced with v0.9
     */
    if (_nextScene)
    {
        setNextScene();
    }

    pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    if (_runningScene)
    {
        //clear draw stats
        _renderer->clearDrawStats();
        
        //render the scene
        if(_openGLView)
        {
            _openGLView->renderScene(_runningScene, _renderer);
        }
    }

    // draw the notifications node
    if (_notificationNode)
    {
        _notificationNode->visit(_renderer, Mat4::IDENTITY, 0);
    }

    updateFrameRate();
    
    _renderer->render();

    popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _totalFrames++;

    // swap buffers
    if (_openGLView)
    {
        _openGLView->swapBuffers();
    }
}

void Director::calculateDeltaTime()
{
    // new delta time. Re-fixed issue #1277
    if (_nextDeltaTimeZero)
    {
        _deltaTime = 0;
        _nextDeltaTimeZero = false;
    }
    else
    {
        // delta time may passed by invoke mainLoop(dt)
        if (!_deltaTimePassedByCaller)
        {
            auto now = std::chrono::steady_clock::now();
            _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
            _lastUpdate = now;
        }
        _deltaTime = MAX(0, _deltaTime);
    }

    // Prevent large delta times
    if (_deltaTime > 5.0 / 60.0f) // 0.2f
    {
        _deltaTime = 1 / 60.0f;
    }
}

float Director::getDeltaTime() const
{
    return _deltaTime;
}
void Director::setOpenGLView(GLView *openGLView)
{
    CCASSERT(openGLView, "opengl view should not be null");

    if (_openGLView != openGLView)
    {
        // Configuration. Gather GPU info
        Configuration *conf = Configuration::getInstance();
        conf->gatherGPUInfo();
        CCLOG("%s\n",conf->getInfo().c_str());

        if(_openGLView)
        {
            _openGLView->release();
        }

        _openGLView = openGLView;
        _openGLView->retain();

        // set size
        _winSizeInPoints = _openGLView->getDesignResolutionSize();

        _isStatusLabelUpdated = true;

        if (_openGLView)
        {
            setGLDefaultValues();
        }

        _renderer->initGLView();

        CHECK_GL_ERROR_DEBUG();
        
        _defaultFBO = cocos_experimental::FrameBuffer::getOrCreateDefaultFBO(_openGLView);
        _defaultFBO->retain();
    }
}

TextureCache* Director::getTextureCache() const
{
    return _textureCache;
}

void Director::initTextureCache()
{
    _textureCache = new (std::nothrow) TextureCache();
}

void Director::destroyTextureCache()
{
    if (_textureCache)
    {
        _textureCache->waitForQuit();
        CC_SAFE_RELEASE_NULL(_textureCache);
    }
}

void Director::setViewport()
{
    if (_openGLView)
    {
        _openGLView->setViewPortInPoints(0, 0, _winSizeInPoints.width, _winSizeInPoints.height);
    }
}

void Director::setNextDeltaTimeZero(bool nextDeltaTimeZero)
{
    _nextDeltaTimeZero = nextDeltaTimeZero;
}

void Director::initMatrixStack()
{
    _matrixStackIndex = 0;
    while (!_textureMatrixStack.empty())
    {
        _textureMatrixStack.pop();
    }

    _modelViewMatrixStack[_matrixStackIndex++] = Mat4::IDENTITY;

    _projectionMatrixStack.push(Mat4::IDENTITY);
    _textureMatrixStack.push(Mat4::IDENTITY);
}

void Director::resetMatrixStack()
{
    initMatrixStack();
}

void Director::initProjectionMatrixStack(size_t stackCount)
{
    _projectionMatrixStack.push(Mat4::IDENTITY);
}

size_t Director::getProjectionMatrixStackSize()
{
    return 1;
}

void Director::popMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _matrixStackIndex--;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.pop();
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void Director::popProjectionMatrix(size_t index)
{
    _projectionMatrixStack.pop();
}

void Director::loadIdentityMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack[_matrixStackIndex - 1] = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = Mat4::IDENTITY;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void Director::loadProjectionIdentityMatrix(size_t index)
{
    _projectionMatrixStack.top() = Mat4::IDENTITY;
}

void Director::loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack[_matrixStackIndex - 1] = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = mat;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void Director::loadProjectionMatrix(const Mat4& mat, size_t index)
{
    _projectionMatrixStack.top() = mat;
}

void Director::multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack[_matrixStackIndex - 1] *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() *= mat;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void Director::multiplyProjectionMatrix(const Mat4& mat, size_t index)
{
    _projectionMatrixStack.top() *= mat;
}

void Director::pushMatrix(MATRIX_STACK_TYPE type)
{
    if(type == MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW)
    {
        _modelViewMatrixStack[_matrixStackIndex] = _modelViewMatrixStack[_matrixStackIndex - 1];
        _matrixStackIndex++;
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION)
    {
        _projectionMatrixStack.push(_projectionMatrixStack.top());
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE)
    {
        _textureMatrixStack.push(_textureMatrixStack.top());
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void Director::pushProjectionMatrix(size_t index)
{
    _projectionMatrixStack.push(_projectionMatrixStack.top());
}

const Mat4& Director::getMatrix(MATRIX_STACK_TYPE type) const
{
    if(type == MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW)
    {
        return _modelViewMatrixStack[_matrixStackIndex - 1];
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION)
    {
        return _projectionMatrixStack.top();
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE)
    {
        return _textureMatrixStack.top();
    }

    CCASSERT(false, "unknown matrix stack type, will return modelview matrix instead");
    return  _modelViewMatrixStack[_matrixStackIndex - 1];
}

const Mat4& Director::getProjectionMatrix(size_t index) const
{
    return _projectionMatrixStack.top();
}

void Director::setProjection(Projection projection)
{
    CSize size = _winSizeInPoints;

    if (size.width == 0 || size.height == 0)
    {
        CCLOGERROR("cocos2d: warning, Director::setProjection() failed because size is 0");
        return;
    }

    setViewport();

    switch (projection)
    {
        case Projection::_2D:
        {
            Mat4 orthoMatrix;
            Mat4::createOrthographicOffCenter(0, size.width, 0, size.height, -1024, 1024, &orthoMatrix);
            loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
            break;
        }
            
        case Projection::_3D:
        {
            float zeye = this->getZEye();

            Mat4 matrixPerspective, matrixLookup;

            // issue #1334
            Mat4::createPerspective(60, (GLfloat)size.width/size.height, 10, zeye+size.height/2, &matrixPerspective);

            Vec3 eye(size.width/2, size.height/2, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
            Mat4::createLookAt(eye, center, up, &matrixLookup);
            Mat4 proj3d = matrixPerspective * matrixLookup;

            loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, proj3d);
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
            break;
        }

        case Projection::CUSTOM:
            // Projection Delegate is no longer needed
            // since the event "PROJECTION CHANGED" is emitted
            break;

        default:
            CCLOG("cocos2d: Director: unrecognized projection");
            break;
    }

    Projection oldProjection = _projection;

    _projection = projection;
    GL::setProjectionMatrixDirty();

    if (_projection != oldProjection)
        _eventDispatcher->dispatchEvent(_eventProjectionChanged);
}

void Director::purgeCachedData(void)
{
    FontAtlasCache::purgeCachedData();

    if (s_SharedDirector->getOpenGLView())
    {
        _textureCache->removeUnusedTextures();

        // Note: some tests such as ActionsTest are leaking refcounted textures
        // There should be no test textures left in the cache
        CCLOG("%s\n", _textureCache->getCachedTextureInfo().c_str());
    }
    FileUtils::getInstance()->purgeCachedEntries();
}

float Director::getZEye(void) const
{
    return (_winSizeInPoints.height / 1.154700538379252f);//(2 * tanf(M_PI/6))
}

void Director::setAlphaBlending(bool on)
{
    if (on)
    {
        GL::blendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    }
    else
    {
        GL::blendFunc(GL_ONE, GL_ZERO);
    }

    CHECK_GL_ERROR_DEBUG();
}

void Director::setDepthTest(bool on)
{
    _renderer->setDepthTest(on);
}

void Director::setClearColor(const Color4F& clearColor)
{
    _renderer->setClearColor(clearColor);
    auto defaultFBO = cocos_experimental::FrameBuffer::getOrCreateDefaultFBO(_openGLView);
    
    if(defaultFBO) defaultFBO->setClearColor(clearColor);
}

static void GLToClipTransform(Mat4 *transformOut)
{
    if(nullptr == transformOut) return;
    
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

    auto projection = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto modelview = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    *transformOut = projection * modelview;
}

Vec2 Director::convertToGL(const Vec2& uiPoint)
{
    Mat4 transform;
    GLToClipTransform(&transform);

    Mat4 transformInv = transform.getInversed();

    // Calculate z=0 using -> transform*[0, 0, 0, 1]/w
    float zClip = transform.m[14]/transform.m[15];

    CSize glSize = _openGLView->getDesignResolutionSize();
    Vec4 clipCoord(2.0f*uiPoint.x/glSize.width - 1.0f, 1.0f - 2.0f*uiPoint.y/glSize.height, zClip, 1);

    Vec4 glCoord;
    //transformInv.transformPoint(clipCoord, &glCoord);
    transformInv.transformVector(clipCoord, &glCoord);
    float factor = 1.0f / glCoord.w;
    return Vec2(glCoord.x * factor, glCoord.y * factor);
}

Vec2 Director::convertToUI(const Vec2& glPoint)
{
    Mat4 transform;
    GLToClipTransform(&transform);

    Vec4 clipCoord;
    // Need to calculate the zero depth from the transform.
    Vec4 glCoord(glPoint.x, glPoint.y, 0.0, 1);
    transform.transformVector(glCoord, &clipCoord);

    /*
    BUG-FIX #5506

    a = (Vx, Vy, Vz, 1)
    b = (a×M)T
    Out = 1 ⁄ bw(bx, by, bz)
    */

    clipCoord.x = clipCoord.x / clipCoord.w;
    clipCoord.y = clipCoord.y / clipCoord.w;
    clipCoord.z = clipCoord.z / clipCoord.w;

    CSize glSize = _openGLView->getDesignResolutionSize();
    float factor = 1.0f / glCoord.w;
    return Vec2(glSize.width * (clipCoord.x * 0.5f + 0.5f) * factor, glSize.height * (-clipCoord.y * 0.5f + 0.5f) * factor);
}

const CSize& Director::getWinSize(void) const
{
    return _winSizeInPoints;
}

CSize Director::getWinSizeInPixels() const
{
    return CSize(_winSizeInPoints.width * _contentScaleFactor, _winSizeInPoints.height * _contentScaleFactor);
}

CSize Director::getVisibleSize() const
{
    if (_openGLView)
    {
        return _openGLView->getVisibleSize();
    }
    else
    {
        return CSize::ZERO;
    }
}

Vec2 Director::getVisibleOrigin() const
{
    if (_openGLView)
    {
        return _openGLView->getVisibleOrigin();
    }
    else
    {
        return Vec2::ZERO;
    }
}

CRect Director::getSafeAreaRect() const
{
    if (_openGLView)
    {
        return _openGLView->getSafeAreaRect();
    }
    else
    {
        return CRect::ZERO;
    }
}

// scene management

void Director::runWithScene(Scene *scene)
{
    CCASSERT(scene != nullptr, "This command can only be used to start the Director. There is already a scene present.");
    CCASSERT(_runningScene == nullptr, "_runningScene should be null");

    pushScene(scene);
    startAnimation();
}

void Director::replaceScene(Scene *scene)
{
    //CCASSERT(_runningScene, "Use runWithScene: instead to start the director");
    CCASSERT(scene != nullptr, "the scene should not be null");
    
    if (_runningScene == nullptr) {
        runWithScene(scene);
        return;
    }
    
    if (scene == _nextScene)
        return;
    
    if (_nextScene)
    {
        if (_nextScene->isRunning())
        {
            _nextScene->onExit();
        }
        _nextScene->cleanup();
        _nextScene = nullptr;
    }

    ssize_t index = _scenesStack.size() - 1;

    _sendCleanupToScene = true;
    _scenesStack.replace(index, scene);

    _nextScene = scene;
}

void Director::pushScene(Scene *scene)
{
    CCASSERT(scene, "the scene should not null");

    _sendCleanupToScene = false;
    _scenesStack.pushBack(scene);
    _nextScene = scene;
}

void Director::popScene(void)
{
    CCASSERT(_runningScene != nullptr, "running scene should not null");
    
    _scenesStack.popBack();
    ssize_t c = _scenesStack.size();

    if (c == 0)
    {
        end();
    }
    else
    {
        _sendCleanupToScene = true;
        _nextScene = _scenesStack.at(c - 1);
    }
}

void Director::popToRootScene(void)
{
    popToSceneStackLevel(1);
}

void Director::popToSceneStackLevel(int level)
{
    CCASSERT(_runningScene != nullptr, "A running Scene is needed");
    ssize_t c = _scenesStack.size();

    // level 0? -> end
    if (level == 0)
    {
        end();
        return;
    }

    // current level or lower -> nothing
    if (level >= c)
        return;

    auto firstOnStackScene = _scenesStack.back();
    if (firstOnStackScene == _runningScene)
    {
        _scenesStack.popBack();
        --c;
    }

    // pop stack until reaching desired level
    while (c > level)
    {
        auto current = _scenesStack.back();

        if (current->isRunning())
        {
            current->onExit();
        }

        current->cleanup();
        _scenesStack.popBack();
        --c;
    }

    _nextScene = _scenesStack.back();

    // cleanup running scene
    _sendCleanupToScene = true;
}

void Director::end()
{
    _purgeDirectorInNextLoop = true;
}

void Director::restart()
{
    _restartDirectorInNextLoop = true;
}

void Director::reset()
{
    if (_runningScene)
    {
        _runningScene->onExit();
        _runningScene->cleanup();
        _runningScene->release();
    }
    
    _runningScene = nullptr;
    _nextScene = nullptr;
    
    // cleanup scheduler
    getScheduler()->unscheduleAll();
    
    if(_notificationNode)
    {
        _notificationNode->onExit();
        _notificationNode->cleanup();
        _notificationNode->release();
    }
    
    _notificationNode = nullptr;
    _scenesStack.clear();
    
    stopAnimation();
    
    CC_SAFE_RELEASE_NULL(_notificationNode);
    
    // purge bitmap cache
    FontAtlasCache::purgeCachedData();
    
    FontFreeType::shutdownFreeType();
    
    // purge all managed caches
    
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    GLProgramCache::destroyInstance();
    GLProgramStateCache::destroyInstance();
    FileUtils::destroyInstance();
    AsyncTaskPool::destroyInstance();
    
    GL::invalidateStateCache();

    RenderState::finalize();
    
    destroyTextureCache();
}

void Director::purgeDirector()
{
    reset();

    CHECK_GL_ERROR_DEBUG();
    
    // OpenGL view
    if (_openGLView)
    {
        _openGLView->end();
        _openGLView = nullptr;
    }
    
    // delete Director
    release();
}

void Director::restartDirector()
{
    reset();
    
    // RenderState need to be reinitialized
    RenderState::initialize();

    // Texture cache need to be reinitialized
    initTextureCache();
    
    // Reschedule for action manager
    _scheduler->schedule(std::bind(&ActionManager::update, getActionManager(), std::placeholders::_1), getActionManager(), "ACTION_MGR_UPDATE");
    
    // release the objects
    PoolManager::getInstance()->getCurrentPool()->clear();

    // Restart animation
    startAnimation();
}

void Director::setNextScene()
{
    if (_runningScene)
    {
        _runningScene->onExitTransitionDidStart();
        _runningScene->onExit();
    }

    // issue #709. the root node (scene) should receive the cleanup message too
    // otherwise it might be leaked.
    if (_sendCleanupToScene && _runningScene)
    {
        _runningScene->cleanup();
    }

    if (_runningScene)
    {
        _runningScene->release();
    }
    _runningScene = _nextScene;
    _nextScene->retain();
    _nextScene = nullptr;

    if (_runningScene)
    {
        _runningScene->onEnter();
        _runningScene->onEnterTransitionDidFinish();
    }
}

void Director::pause()
{
    if (_paused)
    {
        return;
    }

    _oldAnimationInterval = _animationInterval;

    // when paused, don't consume CPU
    setAnimationInterval(1 / 4.0, SetIntervalReason::BY_DIRECTOR_PAUSE);
    _paused = true;
}

void Director::resume()
{
    if (! _paused)
    {
        return;
    }

    setAnimationInterval(_oldAnimationInterval, SetIntervalReason::BY_ENGINE);

    _paused = false;
    _deltaTime = 0;
    // fix issue #3509, skip one fps to avoid incorrect time calculation.
    setNextDeltaTimeZero(true);
}

void Director::updateFrameRate()
{
//    static const float FPS_FILTER = 0.1f;
//    static float prevDeltaTime = 0.016f; // 60FPS
//    
//    float dt = _deltaTime * FPS_FILTER + (1.0f-FPS_FILTER) * prevDeltaTime;
//    prevDeltaTime = dt;
//    _frameRate = 1.0f/dt;

    // Frame rate should be the real value of current frame.
    _frameRate = 1.0f / _deltaTime;
}

void Director::setContentScaleFactor(float scaleFactor)
{
    if (scaleFactor != _contentScaleFactor)
    {
        _contentScaleFactor = scaleFactor;
        _isStatusLabelUpdated = true;
    }
}

void Director::setNotificationNode(Node *node)
{
    if (_notificationNode != nullptr){
        _notificationNode->onExitTransitionDidStart();
        _notificationNode->onExit();
        _notificationNode->cleanup();
    }
    CC_SAFE_RELEASE(_notificationNode);

    _notificationNode = node;
    if (node == nullptr)
        return;
    _notificationNode->onEnter();
    _notificationNode->onEnterTransitionDidFinish();
    CC_SAFE_RETAIN(_notificationNode);
}

void Director::setScheduler(Scheduler* scheduler)
{
    if (_scheduler != scheduler)
    {
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

void Director::setActionManager(ActionManager* actionManager)
{
    if (_actionManager != actionManager)
    {
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }    
}

void Director::startAnimation()
{
    startAnimation(SetIntervalReason::BY_ENGINE);
}

void Director::startAnimation(SetIntervalReason reason)
{
    _lastUpdate = std::chrono::steady_clock::now();

    _invalid = false;

    _cocos2d_thread_id = std::this_thread::get_id();

    Application::getInstance()->setAnimationInterval(_animationInterval, reason);

    // fix issue #3509, skip one fps to avoid incorrect time calculation.
    setNextDeltaTimeZero(true);
}

void Director::mainLoop()
{
    if (_purgeDirectorInNextLoop)
    {
        _purgeDirectorInNextLoop = false;
        purgeDirector();
    }
    else if (_restartDirectorInNextLoop)
    {
        _restartDirectorInNextLoop = false;
        restartDirector();
    }
    else if (! _invalid)
    {
        drawScene();
     
        // release the objects
        PoolManager::getInstance()->getCurrentPool()->clear();
    }
}

void Director::mainLoop(float dt)
{
    _deltaTime = dt;
    _deltaTimePassedByCaller = true;
    mainLoop();
}

void Director::stopAnimation()
{
    _invalid = true;
}

void Director::setAnimationInterval(float interval)
{
    setAnimationInterval(interval, SetIntervalReason::BY_GAME);
}

void Director::setAnimationInterval(float interval, SetIntervalReason reason)
{
    _animationInterval = interval;
    if (! _invalid)
    {
        stopAnimation();
        startAnimation(reason);
    }
}

NS_CC_END

