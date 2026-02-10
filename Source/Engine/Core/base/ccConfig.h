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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "platform/CCPlatformConfig.h"

#ifndef __SSE__
#define __SSE__ 1
#endif

/**
 * @file
 * cocos2d (cc) configuration file.
 */

/** @def CC_ENABLE_STACKABLE_ACTIONS
 * If enabled, actions that alter the position property (eg: MoveBy, JumpBy, BezierBy, etc..) will be stacked.
 * If you run 2 or more 'position' actions at the same time on a node, then end position will be the sum of all the positions.
 * If disabled, only the last run action will take effect.
 * Enabled by default. Disable to be compatible with v2.0 and older versions.
 * @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif

/** @def CC_ENABLE_GL_STATE_CACHE
 * If enabled, cocos2d will maintain an OpenGL state cache internally to avoid unnecessary switches.
 * In order to use them, you have to use the following functions, instead of the GL ones:
 *  - ccGLUseProgram() instead of glUseProgram().
 *  - GL::deleteProgram() instead of glDeleteProgram().
 *  - GL::blendFunc() instead of glBlendFunc().

 * If this functionality is disabled, then ccGLUseProgram(), GL::deleteProgram(), GL::blendFunc() will call the GL ones, without using the cache.

 * It is recommended to enable whenever possible to improve speed.
 * If you are migrating your code from GL ES 1.1, then keep it disabled. Once all your code works as expected, turn it on.

 * Enabled by default.

 * @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif

/** @def CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
 * If enabled, the texture coordinates will be calculated by using this formula:
 * - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
 * - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);

 * The same for bottom and top.

 * This formula prevents artifacts by using 99% of the texture.
 * The "correct" way to prevent artifacts is by using the spritesheet-artifact-fixer.py or a similar tool.

 * Affected nodes:
 * - Sprite / SpriteBatchNode and subclasses: LabelBMFont, TMXTiledMap.
 * - QuadParticleSystem.
 * - TileMap.

 * To enabled set it to 1. Disabled by default.

 * @since v0.99.5
 */
#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0
#endif

/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
 * If enabled, cocos2d-mac will run on the Display Link thread. If disabled cocos2d-mac will run in its own thread.
 * If enabled, the images will be drawn at the "correct" time, but the events might not be very responsive.
 * If disabled, some frames might be skipped, but the events will be dispatched as they arrived.
 * To enable set it to a 1, to disable it set to 0. Enabled by default.
 * Only valid for cocos2d-mac. Not supported on cocos2d-ios.
 */
#ifndef CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1
#endif

/** @def CC_NODE_RENDER_SUBPIXEL
 * If enabled, the Node objects (Sprite, Label,etc) will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 */
#ifndef CC_NODE_RENDER_SUBPIXEL
#define CC_NODE_RENDER_SUBPIXEL 1
#endif

/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 * If enabled, the Sprite objects rendered with SpriteBatchNode will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL    1
#endif

/** @def CC_TEXTURE_ATLAS_USE_VAO
 * By default, TextureAtlas (used by many cocos2d classes) will use VAO (Vertex Array Objects).
 * Apple recommends its usage but they might consume a lot of memory, specially if you use many of them.
 * So for certain cases, where you might need hundreds of VAO objects, it might be a good idea to disable it.
 * To disable it set it to 0. Enabled by default.
 * If a device doesn't support VAO though it claims to support should add exceptions list here.
 */
#ifndef CC_TEXTURE_ATLAS_USE_VAO
#define CC_TEXTURE_ATLAS_USE_VAO 1
#endif


/** @def CC_USE_LA88_LABELS
 * If enabled, it will use LA88 (Luminance Alpha 16-bit textures) for LabelTTF objects.
 * If it is disabled, it will use A8 (Alpha 8-bit textures).
 * LA88 textures are 6% faster than A8 textures, but they will consume 2x memory.
 * This feature is enabled by default.
 * @since v0.99.5
 */
#ifndef CC_USE_LA88_LABELS
#define CC_USE_LA88_LABELS 1
#endif

/** @def CC_SPRITE_DEBUG_DRAW
 * If enabled, all subclasses of Sprite will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default:
 * 0 -- disabled
 * 1 -- draw bounding box
 * 2 -- draw texture box
 */
#ifndef CC_SPRITE_DEBUG_DRAW
#define CC_SPRITE_DEBUG_DRAW 0
#endif

/** @def CC_LABEL_DEBUG_DRAW
 * If enabled, all subclasses of Label will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default:
 * 0 -- disabled
 * 1 -- draw bounding box
 */
#ifndef CC_LABEL_DEBUG_DRAW
#define CC_LABEL_DEBUG_DRAW 0
#endif

/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
 * If enabled, all subclasses of Sprite that are rendered using an SpriteBatchNode draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif

/** @def CC_LABELBMFONT_DEBUG_DRAW
 * If enabled, all subclasses of LabelBMFont will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif


/** @def CC_ENABLE_ALLOCATOR
 * Turn on creation of global allocator and pool allocators
 * as specified by CC_ALLOCATOR_GLOBAL below.
 */
#ifndef CC_ENABLE_ALLOCATOR
# define CC_ENABLE_ALLOCATOR 0
#endif

/** @def CC_ENABLE_ALLOCATOR_DIAGNOSTICS
 * Turn on debugging of allocators. This is slower, uses
 * more memory, and should not be used for production builds.
 */
#ifndef CC_ENABLE_ALLOCATOR_DIAGNOSTICS
# define CC_ENABLE_ALLOCATOR_DIAGNOSTICS CC_ENABLE_ALLOCATOR
#endif

/** @def CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
 * Turn on override of global new and delete
 * as specified by CC_ALLOCATOR_GLOBAL_NEW_DELETE below.
 */
#ifndef CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE 0
# endif//CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE

/** @def CC_ALLOCATOR_GLOBAL
 * Specify allocator to use for global allocator.
 */
#ifndef CC_ALLOCATOR_GLOBAL
# define CC_ALLOCATOR_GLOBAL cocos2d::allocator::AllocatorStrategyDefault
#endif

/** @def CC_ALLOCATOR_GLOBAL_NEW_DELETE
 * Specify allocator to use when overriding of new and delete.
 */
#ifndef CC_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ALLOCATOR_GLOBAL_NEW_DELETE cocos2d::allocator::AllocatorStrategyGlobalSmallBlock
#endif

#ifndef CC_FILEUTILS_APPLE_ENABLE_OBJC
#define CC_FILEUTILS_APPLE_ENABLE_OBJC  1
#endif

#endif // __CCCONFIG_H__
