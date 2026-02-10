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

#include "2d/CCSprite.h"

#include <algorithm>

#include "2d/CCCamera.h"
#include "2d/CCSpriteBatchNode.h"
#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

static unsigned short quadIndices9[]={
    0+4*0,1+4*0,2+4*0, 3+4*0,2+4*0,1+4*0,
    0+4*1,1+4*1,2+4*1, 3+4*1,2+4*1,1+4*1,
    0+4*2,1+4*2,2+4*2, 3+4*2,2+4*2,1+4*2,
    0+4*3,1+4*3,2+4*3, 3+4*3,2+4*3,1+4*3,
    0+4*4,1+4*4,2+4*4, 3+4*4,2+4*4,1+4*4,
    0+4*5,1+4*5,2+4*5, 3+4*5,2+4*5,1+4*5,
    0+4*6,1+4*6,2+4*6, 3+4*6,2+4*6,1+4*6,
    0+4*7,1+4*7,2+4*7, 3+4*7,2+4*7,1+4*7,
    0+4*8,1+4*8,2+4*8, 3+4*8,2+4*8,1+4*8,
};

// MARK: create, init, dealloc
Sprite* Sprite::createWithTexture(Texture2D *texture)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite)
    {
        if (sprite->initWithTexture(texture))
        {
            sprite->autorelease();
            return sprite;
        }
        else
        {
            // Zac : just return an empty sprite to prevent dumb crashes
            sprite->autorelease();
            return sprite;
        }
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::createWithTexture(Texture2D *texture, const CRect& rect, bool rotated)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite)
    {
        if (sprite->initWithTexture(texture, rect, rotated))
        {
            sprite->autorelease();
            return sprite;
        }
        else
        {
            // Zac : just return an empty sprite to prevent dumb crashes
            sprite->autorelease();
            return sprite;
        }
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create(const std::string& filename)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite)
    {
        if (sprite->initWithFile(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        else
        {
            // Zac : just return an empty sprite to prevent dumb crashes
            sprite->autorelease();
            return sprite;
        }
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create(const std::string& filename, const CRect& rect)
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite)
    {
        if (sprite->initWithFile(filename, rect))
        {
            sprite->autorelease();
            return sprite;
        }
        else
        {
            // Zac : just return an empty sprite to prevent dumb crashes
            sprite->autorelease();
            return sprite;
        }
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite* Sprite::create()
{
    Sprite *sprite = new (std::nothrow) Sprite();
    if (sprite)
    {
        if (sprite->init())
        {
            sprite->autorelease();
            return sprite;
        }
        else
        {
            // Zac : just return an empty sprite to prevent dumb crashes
            sprite->autorelease();
            return sprite;
        }
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Sprite::init()
{
    initWithTexture(nullptr, CRect::ZERO);

    return true;
}

bool Sprite::initWithTexture(Texture2D *texture)
{
    CCASSERT(texture != nullptr, "Invalid texture for sprite");

    CRect rect = CRect::ZERO;
    if (texture) {
        rect.size = texture->getContentSize();
    }

    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithTexture(Texture2D *texture, const CRect& rect)
{
    return initWithTexture(texture, rect, false);
}

bool Sprite::initWithFile(const std::string& filename)
{
    if (filename.empty())
    {
        CCLOG("Call Sprite::initWithFile with blank resource filename.");
        return false;
    }

    _fileName = filename;
    _fileType = 0;

    Texture2D *texture = _director->getTextureCache()->addImage(filename);
    if (texture)
    {
        CRect rect = CRect::ZERO;
        rect.size = texture->getContentSize();
        return initWithTexture(texture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release();
    return false;
}

bool Sprite::initWithFile(const std::string &filename, const CRect& rect)
{
    CCASSERT(!filename.empty(), "Invalid filename");
    if (filename.empty())
    {
        return false;
    }

    _fileName = filename;
    _fileType = 0;

    Texture2D *texture = _director->getTextureCache()->addImage(filename);
    if (texture)
    {
        return initWithTexture(texture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release();
    return false;
}

// designated initializer
bool Sprite::initWithTexture(Texture2D *texture, const CRect& rect, bool rotated)
{
    bool result = false;
    if (Node::init())
    {
        _batchNode = nullptr;

        _recursiveDirty = false;
        setDirty(false);

        _opacityModifyRGB = true;

        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

        _flippedX = _flippedY = false;

        // default transform anchor: center
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);

        // zwoptex default values
        _offsetPosition.setZero();

        // clean the Quad
        memset(&_quad, 0, sizeof(_quad));

        // Atlas: Color
        _quad.bl.colors = Color4B::WHITE;
        _quad.br.colors = Color4B::WHITE;
        _quad.tl.colors = Color4B::WHITE;
        _quad.tr.colors = Color4B::WHITE;

        // update texture (calls updateBlendFunc)
        setTexture(texture);
        setTextureRect(rect, rotated, rect.size);

        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        setBatchNode(nullptr);
        result = true;
    }

    _recursiveDirty = true;
    setDirty(true);

    return result;
}

Sprite::Sprite(void)
: _batchNode(nullptr)
, _textureAtlas(nullptr)
, _shouldBeHidden(false)
, _texture(nullptr)
, _insideBounds(true)
, _centerRectNormalized(0,0,1,1)
, _renderMode(Sprite::RenderMode::QUAD)
, _trianglesVertex(nullptr)
, _trianglesIndex(nullptr)
, _stretchFactor(Vec2::ONE)
, _originalContentSize(CSize::ZERO)
, _stretchEnabled(true)
{
}

Sprite::~Sprite()
{
    CC_SAFE_FREE(_trianglesVertex);
    CC_SAFE_FREE(_trianglesIndex);
    CC_SAFE_RELEASE(_texture);
}

/*
 * Texture methods
 */

/*
 * This array is the data of a white image with 2 by 2 dimension.
 * It's used for creating a default texture when sprite's texture is set to nullptr.
 * Supposing codes as follows:
 *
 *   auto sp = new (std::nothrow) Sprite();
 *   sp->init();  // Texture was set to nullptr, in order to make opacity and color to work correctly, we need to create a 2x2 white texture.
 *
 * The test is in "TestCpp/SpriteTest/Sprite without texture".
 */
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "/cc_2x2_white_image"

// MARK: texture
void Sprite::setTexture(const std::string &filename)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    setTexture(texture);
    _unflippedOffsetPositionFromCenter = Vec2::ZERO;
    CRect rect = CRect::ZERO;
    if (texture)
        rect.size = texture->getContentSize();
    setTextureRect(rect);
}

void Sprite::setTexture(Texture2D *texture)
{
    if(_glProgramState == nullptr)
    {
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, texture));
    }
    // If batchnode, then texture id should be the same
    CCASSERT(! _batchNode || (texture &&  texture->getName() == _batchNode->getTexture()->getName()), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");

    if (texture == nullptr)
    {
        // Gets the texture by key firstly.
        texture = _director->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);

        // If texture wasn't in cache, create it from RAW data.
        if (texture == nullptr)
        {
            Image* image = new (std::nothrow) Image();
            bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
            CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");

            texture = _director->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY);
            CC_SAFE_RELEASE(image);
        }
    }

    if ((_renderMode != RenderMode::QUAD_BATCHNODE) && (_texture != texture))
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
        updateBlendFunc();
    }
}

Texture2D* Sprite::getTexture() const
{
    return _texture;
}

void Sprite::setTextureRect(const CRect& rect)
{
    setTextureRect(rect, false, rect.size);
}

void Sprite::setTextureRect(const CRect& rect, bool rotated, const CSize& untrimmedSize)
{
    _rectRotated = rotated;

    Node::setContentSize(untrimmedSize);
    _originalContentSize = untrimmedSize;

    setVertexRect(rect);
    updateStretchFactor();
    updatePoly();
}

void Sprite::updatePoly()
{
    // There are 3 cases:
    //
    // A) a non 9-sliced, non stretched
    //    contentsize doesn't not affect the stretching, since there is no stretching
    //    this was the original behavior, and we keep it for backwards compatibility reasons
    //    When non-stretching is enabled, we have to change the offset in order to "fill the empty" space at the
    //    left-top of the texture
    // B) non 9-sliced, stretched
    //    the texture is stretched to the content size
    // C) 9-sliced, stretched
    //    the sprite is 9-sliced and stretched.
    if (_renderMode == RenderMode::QUAD || _renderMode == RenderMode::QUAD_BATCHNODE)
    {
        CRect copyRect;
        if (_stretchEnabled)
        {
            // case B)
            copyRect = CRect(0, 0, _rect.size.width * _stretchFactor.x, _rect.size.height * _stretchFactor.y);
        }
        else
        {
            // case A)
            // modify origin to put the sprite in the correct offset
            copyRect = CRect((_contentSize.width - _originalContentSize.width) / 2.0f,
                            (_contentSize.height - _originalContentSize.height) / 2.0f,
                            _rect.size.width,
                            _rect.size.height);
        }

        setTextureCoords(_rect, &_quad);
        setVertexCoords(copyRect, &_quad);
        
        triangles.indices = quadIndices9;
        triangles.vertCount = 4;
        triangles.indexCount = 6;
        triangles.verts = (V3F_C4B_T2F*)&_quad;
    } 
}

// override this method to generate "double scale" sprites
void Sprite::setVertexRect(const CRect& rect)
{
    _rect = rect;
}

void Sprite::setTextureCoords(const CRect& rectInPoints)
{
    setTextureCoords(rectInPoints, &_quad);
}

void Sprite::setTextureCoords(const CRect& rectInPoints, V3F_C4B_T2F_Quad* outQuad)
{
    Texture2D *tex = (_renderMode == RenderMode::QUAD_BATCHNODE) ? _textureAtlas->getTexture() : _texture;
    if (tex == nullptr)
    {
        return;
    }

    const auto rectInPixels = CC_RECT_POINTS_TO_PIXELS(rectInPoints);

    const float atlasWidth = (float)tex->getPixelsWide();
    const float atlasHeight = (float)tex->getPixelsHigh();

    float rw = rectInPixels.size.width;
    float rh = rectInPixels.size.height;

    // if the rect is rotated, it means that the frame is rotated 90 degrees (clockwise) and:
    //  - rectInpoints: origin will be the bottom-left of the frame (and not the top-right)
    //  - size: represents the unrotated texture size
    //
    // so what we have to do is:
    //  - swap texture width and height
    //  - take into account the origin
    //  - flip X instead of Y when flipY is enabled
    //  - flip Y instead of X when flipX is enabled

    if (_rectRotated)
        std::swap(rw, rh);

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    float left    = (2*rectInPixels.origin.x+1) / (2*atlasWidth);
    float right   = left+(rw*2-2) / (2*atlasWidth);
    float top     = (2*rectInPixels.origin.y+1) / (2*atlasHeight);
    float bottom  = top+(rh*2-2) / (2*atlasHeight);
#else
    float left    = rectInPixels.origin.x / atlasWidth;
    float right   = (rectInPixels.origin.x + rw) / atlasWidth;
    float top     = rectInPixels.origin.y / atlasHeight;
    float bottom  = (rectInPixels.origin.y + rh) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL


    if ((!_rectRotated && _flippedX) || (_rectRotated && _flippedY))
    {
        std::swap(left, right);
    }

    if ((!_rectRotated && _flippedY) || (_rectRotated && _flippedX))
    {
        std::swap(top, bottom);
    }

    if (_rectRotated)
    {
        outQuad->bl.texCoords.u = left;
        outQuad->bl.texCoords.v = top;
        outQuad->br.texCoords.u = left;
        outQuad->br.texCoords.v = bottom;
        outQuad->tl.texCoords.u = right;
        outQuad->tl.texCoords.v = top;
        outQuad->tr.texCoords.u = right;
        outQuad->tr.texCoords.v = bottom;
    }
    else
    {
        outQuad->bl.texCoords.u = left;
        outQuad->bl.texCoords.v = bottom;
        outQuad->br.texCoords.u = right;
        outQuad->br.texCoords.v = bottom;
        outQuad->tl.texCoords.u = left;
        outQuad->tl.texCoords.v = top;
        outQuad->tr.texCoords.u = right;
        outQuad->tr.texCoords.v = top;
    }
}

void Sprite::setVertexCoords(const CRect& rect, V3F_C4B_T2F_Quad* outQuad)
{
    float relativeOffsetX = _unflippedOffsetPositionFromCenter.x;
    float relativeOffsetY = _unflippedOffsetPositionFromCenter.y;

    // issue #732
    if (_flippedX)
    {
        relativeOffsetX = -relativeOffsetX;
    }
    if (_flippedY)
    {
        relativeOffsetY = -relativeOffsetY;
    }

    _offsetPosition.x = relativeOffsetX + (_originalContentSize.width - _rect.size.width) / 2;
    _offsetPosition.y = relativeOffsetY + (_originalContentSize.height - _rect.size.height) / 2;

    // FIXME: Stretching should be applied to the "offset" as well
    // but probably it should be calculated in the caller function. It will be tidier
    if (_renderMode == RenderMode::QUAD) {
        _offsetPosition.x *= _stretchFactor.x;
        _offsetPosition.y *= _stretchFactor.y;
    }

    // rendering using batch node
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering

        // Atlas: Vertex
        const float x1 = 0.0f + _offsetPosition.x + rect.origin.x;
        const float y1 = 0.0f + _offsetPosition.y + rect.origin.y;
        const float x2 = x1 + rect.size.width;
        const float y2 = y1 + rect.size.height;

        // Don't update Z.
        outQuad->bl.vertices.set(x1, y1, 0.0f);
        outQuad->br.vertices.set(x2, y1, 0.0f);
        outQuad->tl.vertices.set(x1, y2, 0.0f);
        outQuad->tr.vertices.set(x2, y2, 0.0f);
    }
}

void Sprite::populateTriangle(int quadIndex, const V3F_C4B_T2F_Quad& quad)
{
    CCASSERT(quadIndex < 9, "Invalid quadIndex");
    // convert Quad intro Triangle since it takes less memory

    // Triangles are ordered like the following:
    //   Numbers: Quad Index
    //   Letters: triangles' vertices
    //
    //  M-----N-----O-----P
    //  |     |     |     |
    //  |  6  |  7  |  8  |
    //  |     |     |     |
    //  I-----J-----K-----L
    //  |     |     |     |
    //  |  3  |  4  |  5  |
    //  |     |     |     |
    //  E-----F-----G-----H
    //  |     |     |     |
    //  |  0  |  1  |  2  |
    //  |     |     |     |
    //  A-----B-----C-----D
    //
    // So, if QuadIndex == 4, then it should update vertices J,K,F,G

    // Optimization: I don't need to copy all the vertices all the time. just the 4 "quads" from the corners.
    if (quadIndex == 0 || quadIndex == 2 || quadIndex == 6 || quadIndex == 8)
    {
        if (_flippedX) {
            if (quadIndex % 3 == 0)
                quadIndex += 2;
            else
                quadIndex -= 2;
        }

        if (_flippedY) {
            if (quadIndex <= 2)
                quadIndex += 6;
            else
                quadIndex -= 6;
        }

        const int index_bl = quadIndex * 4 / 3;
        const int index_br = index_bl + 1;
        const int index_tl = index_bl + 4;
        const int index_tr = index_bl + 5;
        

        _trianglesVertex[index_tr] = quad.tr;
        _trianglesVertex[index_br] = quad.br;
        _trianglesVertex[index_tl] = quad.tl;
        _trianglesVertex[index_bl] = quad.bl;
    }
}


// MARK: visit, draw, transform

void Sprite::updateTransform(void)
{
    CCASSERT(_renderMode == RenderMode::QUAD_BATCHNODE, "updateTransform is only valid when Sprite is being rendered using an SpriteBatchNode");

    // recalculate matrix only if it is dirty
    if( isDirty() ) {

        // If it is not visible, or one of its ancestors is not visible, then do nothing:
        if( !_visible || ( _parent && _parent != _batchNode && static_cast<Sprite*>(_parent)->_shouldBeHidden) )
        {
            _quad.br.vertices.setZero();
            _quad.tl.vertices.setZero();
            _quad.tr.vertices.setZero();
            _quad.bl.vertices.setZero();
            _shouldBeHidden = true;
        }
        else
        {
            _shouldBeHidden = false;

            if( ! _parent || _parent == _batchNode )
            {
                _transformToBatch = getNodeToParentTransform();
            }
            else
            {
                CCASSERT( dynamic_cast<Sprite*>(_parent), "Logic error in Sprite. Parent must be a Sprite");
                const Mat4 &nodeToParent = getNodeToParentTransform();
                Mat4 &parentTransform = static_cast<Sprite*>(_parent)->_transformToBatch;
                _transformToBatch = parentTransform * nodeToParent;
            }

            //
            // calculate the Quad based on the Affine Matrix
            //

            CSize &size = _rect.size;

            float x1 = _offsetPosition.x;
            float y1 = _offsetPosition.y;

            float x2 = x1 + size.width;
            float y2 = y1 + size.height;

            float x = _transformToBatch.m[12];
            float y = _transformToBatch.m[13];

            float cr = _transformToBatch.m[0];
            float sr = _transformToBatch.m[1];
            float cr2 = _transformToBatch.m[5];
            float sr2 = -_transformToBatch.m[4];
            float ax = x1 * cr - y1 * sr2 + x;
            float ay = x1 * sr + y1 * cr2 + y;

            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;

            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;

            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;

            _quad.bl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(ax), SPRITE_RENDER_IN_SUBPIXEL(ay), _positionZ);
            _quad.br.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(bx), SPRITE_RENDER_IN_SUBPIXEL(by), _positionZ);
            _quad.tl.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(dx), SPRITE_RENDER_IN_SUBPIXEL(dy), _positionZ);
            _quad.tr.vertices.set(SPRITE_RENDER_IN_SUBPIXEL(cx), SPRITE_RENDER_IN_SUBPIXEL(cy), _positionZ);
            setTextureCoords(_rect);
        }

        // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
        if (_textureAtlas)
        {
            _textureAtlas->updateQuad(&_quad, _atlasIndex);
        }

        _recursiveDirty = false;
        setDirty(false);
    }

    // MARMALADE CHANGED
    // recursively iterate over children
/*    if( _hasChildren )
    {
        // MARMALADE: CHANGED TO USE Node*
        // NOTE THAT WE HAVE ALSO DEFINED virtual Node::updateTransform()
        arrayMakeObjectsPerformSelector(_children, updateTransform, Sprite*);
    }*/
    Node::updateTransform();
}

// draw

void Sprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_texture == nullptr)
    {
        return;
    }

    _trianglesCommand.init(0.0f,
                            _texture,
                            getGLProgramState(),
                            _blendFunc,
                            triangles,
                            transform,
                            flags);

    renderer->addCommand(&_trianglesCommand);
}

// MARK: visit, draw, transform

void Sprite::addChild(Node *child, int zOrder)
{
    CCASSERT(child != nullptr, "Argument must be non-nullptr");
    if (child == nullptr)
    {
        return;
    }

    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        Sprite* childSprite = dynamic_cast<Sprite*>(child);
        CCASSERT( childSprite, "CCSprite only supports Sprites as children when using SpriteBatchNode");
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "childSprite's texture name should be equal to _textureAtlas's texture name!");
        //put it in descendants array of batch node
        _batchNode->appendChild(childSprite);

        if (!_reorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
    Node::addChild(child, zOrder);
}

void Sprite::addChild(Node *child, int zOrder, const std::string &name)
{
    CCASSERT(child != nullptr, "Argument must be non-nullptr");
    if (child == nullptr)
    {
        return;
    }

    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        Sprite* childSprite = dynamic_cast<Sprite*>(child);
        CCASSERT( childSprite, "CCSprite only supports Sprites as children when using SpriteBatchNode");
        CCASSERT(childSprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(),
                 "childSprite's texture name should be equal to _textureAtlas's texture name.");
        //put it in descendants array of batch node
        _batchNode->appendChild(childSprite);

        if (!_reorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
    Node::addChild(child, zOrder, name);
}

void Sprite::reorderChild(Node *child, int zOrder)
{
    CCASSERT(child != nullptr, "child must be non null");
    CCASSERT(_children.contains(child), "child does not belong to this");

    if ((_renderMode == RenderMode::QUAD_BATCHNODE) && ! _reorderChildDirty)
    {
        setReorderChildDirtyRecursively();
        _batchNode->reorderBatch(true);
    }

    Node::reorderChild(child, zOrder);
}

void Sprite::removeChild(Node *child, bool cleanup)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        _batchNode->removeSpriteFromAtlas((Sprite*)(child));
    }

    Node::removeChild(child, cleanup);
}

void Sprite::removeAllChildrenWithCleanup(bool cleanup)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        for(const auto &child : _children) {
            Sprite* sprite = dynamic_cast<Sprite*>(child);
            if (sprite)
            {
                _batchNode->removeSpriteFromAtlas(sprite);
            }
        }
    }

    Node::removeAllChildrenWithCleanup(cleanup);
}

void Sprite::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        sortNodes(_children);

        if (_renderMode == RenderMode::QUAD_BATCHNODE)
        {
            for(const auto &child : _children)
                child->sortAllChildren();
        }

        _reorderChildDirty = false;
    }
}

//
// Node property overloads
// used only when parent is SpriteBatchNode
//

void Sprite::setReorderChildDirtyRecursively(void)
{
    //only set parents flag the first time
    if ( ! _reorderChildDirty )
    {
        _reorderChildDirty = true;
        Node* node = static_cast<Node*>(_parent);
        while (node && node != _batchNode)
        {
            static_cast<Sprite*>(node)->setReorderChildDirtyRecursively();
            node=node->getParent();
        }
    }
}

void Sprite::setDirtyRecursively(bool bValue)
{
    _recursiveDirty = bValue;
    setDirty(bValue);

    for(const auto &child: _children) {
        Sprite* sp = dynamic_cast<Sprite*>(child);
        if (sp)
        {
            sp->setDirtyRecursively(true);
        }
    }
}

// FIXME: HACK: optimization
#define SET_DIRTY_RECURSIVELY() {                       \
                    if (! _recursiveDirty) {            \
                        _recursiveDirty = true;         \
                        setDirty(true);                 \
                        if (!_children.empty())         \
                            setDirtyRecursively(true);  \
                        }                               \
                    }

void Sprite::setPosition(const Vec2& pos)
{
    Node::setPosition(pos);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setPosition(float x, float y)
{
    Node::setPosition(x, y);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setRotation(float rotation)
{
    Node::setRotation(rotation);

    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScaleX(float scaleX)
{
    Node::setScaleX(scaleX);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setScaleY(float scaleY)
{
    Node::setScaleY(scaleY);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setPositionZ(float fVertexZ)
{
    Node::setPositionZ(fVertexZ);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setAnchorPoint(const Vec2& anchor)
{
    Node::setAnchorPoint(anchor);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setIgnoreAnchorPointForPosition(bool value)
{
    CCASSERT(_renderMode != RenderMode::QUAD_BATCHNODE, "setIgnoreAnchorPointForPosition is invalid in Sprite");
    Node::setIgnoreAnchorPointForPosition(value);
}

void Sprite::setVisible(bool bVisible)
{
    Node::setVisible(bVisible);
    SET_DIRTY_RECURSIVELY();
}

void Sprite::setContentSize(const CSize& size)
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE || _renderMode == RenderMode::POLYGON)
        CCLOGWARN("Sprite::setContentSize() doesn't stretch the sprite when using QUAD_BATCHNODE or POLYGON render modes");

    Node::setContentSize(size);

    updateStretchFactor();
    updatePoly();
}

void Sprite::updateStretchFactor()
{
    const CSize size = getContentSize();

    if (_renderMode == RenderMode::QUAD)
    {
        // If stretch is disabled, calculate the stretch anyway
        // since it is needed to calculate the offset
        const float x_factor = size.width / _originalContentSize.width;
        const float y_factor = size.height / _originalContentSize.height;

        _stretchFactor = Vec2(std::max(0.0f, x_factor),
                              std::max(0.0f, y_factor));
    }
    else if (_renderMode == RenderMode::SLICE9)
    {
        const float x1 = _rect.size.width * _centerRectNormalized.origin.x;
        const float x2 = _rect.size.width * _centerRectNormalized.size.width;
        const float x3 = _rect.size.width * (1 - _centerRectNormalized.origin.x - _centerRectNormalized.size.width);

        const float y1 = _rect.size.height * _centerRectNormalized.origin.y;
        const float y2 = _rect.size.height * _centerRectNormalized.size.height;
        const float y3 = _rect.size.height * (1 - _centerRectNormalized.origin.y - _centerRectNormalized.size.height);

        // adjustedSize = the new _rect size
        const float adjustedWidth = size.width - (_originalContentSize.width - _rect.size.width);
        const float adjustedHeight = size.height - (_originalContentSize.height - _rect.size.height);

        const float x_factor = (adjustedWidth - x1 - x3) / x2;
        const float y_factor = (adjustedHeight - y1 - y3) / y2;

        _stretchFactor = Vec2(std::max(0.0f, x_factor),
                              std::max(0.0f, y_factor));
    }

    // else:
    // Do nothing if renderMode is Polygon
}

void Sprite::setFlippedX(bool flippedX)
{
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        flipX();
    }
}

bool Sprite::isFlippedX(void) const
{
    return _flippedX;
}

void Sprite::setFlippedY(bool flippedY)
{
    if (_flippedY != flippedY)
    {
        _flippedY = flippedY;
        flipY();
    }
}

bool Sprite::isFlippedY(void) const
{
    return _flippedY;
}

void Sprite::flipX()
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        setDirty(true);
    }
    else
    {
        // RenderMode:: Quad or Slice9
        updatePoly();
    }
}

void Sprite::flipY()
{
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        setDirty(true);
    }
    else
    {
        // RenderMode:: Quad or Slice9
        updatePoly();
    }
}

//
// MARK: RGBA protocol
//

void Sprite::updateColor(void)
{
    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

    // special opacity for premultiplied textures
    if (_opacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }

    // related to issue #17116
    // when switching from Quad to Slice9, the color will be obtained from _quad
    // so it is important to update _quad colors as well.
    _quad.bl.colors = _quad.tl.colors = _quad.br.colors = _quad.tr.colors = color4;

    // renders using batch node
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
    {
        if (_atlasIndex != INDEX_NOT_INITIALIZED)
        {
            _textureAtlas->updateQuad(&_quad, _atlasIndex);
        }
        else
        {
            // no need to set it recursively
            // update dirty_, don't update recursiveDirty_
            setDirty(true);
        }
    }

    // self render
    // do nothing
}

void Sprite::setOpacityModifyRGB(bool modify)
{
    if (_opacityModifyRGB != modify)
    {
        _opacityModifyRGB = modify;
        updateColor();
    }
}

bool Sprite::isOpacityModifyRGB(void) const
{
    return _opacityModifyRGB;
}

SpriteBatchNode* Sprite::getBatchNode() const
{
    return _batchNode;
}

void Sprite::setBatchNode(SpriteBatchNode *spriteBatchNode)
{
    _batchNode = spriteBatchNode; // weak reference

    // self render
    if( ! _batchNode ) {
        if (_renderMode != RenderMode::SLICE9) {
            _renderMode = RenderMode::QUAD;
        }
        _atlasIndex = INDEX_NOT_INITIALIZED;
        setTextureAtlas(nullptr);
        _recursiveDirty = false;
        setDirty(false);

        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;
        float x2 = x1 + _rect.size.width;
        float y2 = y1 + _rect.size.height;
        _quad.bl.vertices.set( x1, y1, 0 );
        _quad.br.vertices.set(x2, y1, 0);
        _quad.tl.vertices.set(x1, y2, 0);
        _quad.tr.vertices.set(x2, y2, 0);

    }
    else
    {
        // using batch
        _renderMode = RenderMode::QUAD_BATCHNODE;
        _transformToBatch = Mat4::IDENTITY;
        setTextureAtlas(_batchNode->getTextureAtlas()); // weak ref
    }
}

// MARK: Texture protocol

void Sprite::updateBlendFunc(void)
{
    CCASSERT(_renderMode != RenderMode::QUAD_BATCHNODE, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a SpriteBatchNode");

    // it is possible to have an untextured sprite
    if (! _texture || ! _texture->hasPremultipliedAlpha())
    {
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
        setOpacityModifyRGB(false);
    }
    else
    {
        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
        setOpacityModifyRGB(true);
    }
}

std::string Sprite::getDescription() const
{
    int texture_id = -1;
    if (_renderMode == RenderMode::QUAD_BATCHNODE)
        texture_id = _batchNode->getTextureAtlas()->getTexture()->getName();
    else
        texture_id = _texture->getName();
    return StringUtils::format("<Sprite | Tag = %d, TextureID = %d>", -1, texture_id );
}

NS_CC_END
