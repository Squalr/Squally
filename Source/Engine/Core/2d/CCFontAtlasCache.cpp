/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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
#include "2d/CCFontAtlasCache.h"

#include "base/CCDirector.h"
#include "2d/CCFontFreeType.h"
#include "2d/CCFontAtlas.h"
#include "2d/CCLabel.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

std::unordered_map<std::string, FontAtlas *> FontAtlasCache::_atlasMap;
#define ATLAS_MAP_KEY_BUFFER 255

void FontAtlasCache::purgeCachedData()
{
    auto atlasMapCopy = _atlasMap;
    for (auto&& atlas : atlasMapCopy)
    {
        auto refCount = atlas.second->getReferenceCount();
        atlas.second->release();
        if (refCount != 1)
            atlas.second->purgeTexturesAtlas();
    }
    _atlasMap.clear();
}

FontAtlas* FontAtlasCache::getFontAtlasTTF(const _ttfConfig* config)
{
    auto realFontFilename = FileUtils::getInstance()->getNewFilename(config->fontFilePath);  // resolves real file path, to prevent storing multiple atlases for the same file.
    bool useDistanceField = config->distanceFieldEnabled;
    if(config->outlineSize > 0)
    {
        useDistanceField = false;
    }

    char tmp[ATLAS_MAP_KEY_BUFFER];
    if (useDistanceField) {
        snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "df %.2f %d %s", config->fontSize, config->outlineSize,
                 realFontFilename.c_str());
    } else {
        snprintf(tmp, ATLAS_MAP_KEY_BUFFER, "%.2f %d %s", config->fontSize, config->outlineSize,
                 realFontFilename.c_str());
    }
    std::string atlasName = tmp;

    auto it = _atlasMap.find(atlasName);

    if ( it == _atlasMap.end() )
    {
        auto font = FontFreeType::create(realFontFilename, config->fontSize, config->glyphs,
            config->customGlyphs, useDistanceField, config->outlineSize);
        if (font)
        {
            auto tempAtlas = font->createFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return _atlasMap[atlasName];

    return nullptr;
}

bool FontAtlasCache::releaseFontAtlas(FontAtlas *atlas)
{
    if (nullptr != atlas)
    {
        for( auto &item: _atlasMap )
        {
            if ( item.second == atlas )
            {
                if (atlas->getReferenceCount() == 1)
                {
                  _atlasMap.erase(item.first);
                }
                
                atlas->release();
                
                return true;
            }
        }
    }
    
    return false;
}

void FontAtlasCache::unloadFontAtlasTTF(const std::string& fontFileName)
{
    auto item = _atlasMap.begin();
    while (item != _atlasMap.end())
    {
        if (item->first.find(fontFileName) != std::string::npos)
        {
            CC_SAFE_RELEASE_NULL(item->second);
            item = _atlasMap.erase(item);
        }
        else
            item++;
    }
}

NS_CC_END
