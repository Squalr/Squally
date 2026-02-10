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

#include "2d/CCLabel.h"

#include <algorithm>

#include "2d/CCCamera.h"
#include "2d/CCDrawNode.h"
#include "2d/CCFont.h"
#include "2d/CCFontAtlasCache.h"
#include "2d/CCFontAtlas.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventCustom.h"
#include "base/ccUTF8.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"

NS_CC_BEGIN

/**
 * LabelLetter used to update the quad in texture atlas without SpriteBatchNode.
 */
class LabelLetter : public Sprite
{
public:
    LabelLetter()
    {
        _textureAtlas = nullptr;
        _letterVisible = true;
    }

    static LabelLetter* createWithTexture(Texture2D *texture, const CRect& rect, bool rotated = false)
    {
        auto letter = new (std::nothrow) LabelLetter();
        if (letter && letter->initWithTexture(texture, rect, rotated))
        {
            letter->Sprite::setVisible(false);
            letter->autorelease();
            return letter;
        }
        CC_SAFE_DELETE(letter);
        return nullptr;
    }
    
    CREATE_FUNC(LabelLetter);

    virtual void updateTransform() override
    {
        if (isDirty())
        {
            _transformToBatch = getNodeToParentTransform();
            CSize& size = _rect.size;

            float x1 = _offsetPosition.x;
            float y1 = _offsetPosition.y;
            float x2 = x1 + size.width;
            float y2 = y1 + size.height;

            // issue #17022: don't flip, again, the letter since they are flipped in sprite's code
            //if (_flippedX) std::swap(x1, x2);
            //if (_flippedY) std::swap(y1, y2);

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

            if (_textureAtlas)
            {
                _textureAtlas->updateQuad(&_quad, _atlasIndex);
            }

            _recursiveDirty = false;
            setDirty(false);
        }

        Node::updateTransform();
    }

    virtual void updateColor() override
    {
        if (_textureAtlas == nullptr)
        {
            return;
        }

        auto displayedOpacity = _displayedOpacity;
        if(!_letterVisible)
        {
            displayedOpacity = 0.0f;
        }
        Color4B color4(_displayedColor.r, _displayedColor.g, _displayedColor.b, displayedOpacity);
        // special opacity for premultiplied textures
        if (_opacityModifyRGB)
        {
            color4.r *= displayedOpacity / 255.0f;
            color4.g *= displayedOpacity / 255.0f;
            color4.b *= displayedOpacity / 255.0f;
        }
        _quad.bl.colors = color4;
        _quad.br.colors = color4;
        _quad.tl.colors = color4;
        _quad.tr.colors = color4;

        _textureAtlas->updateQuad(&_quad, _atlasIndex);
    }

    void setVisible(bool visible) override
    {
        _letterVisible = visible;
        updateColor();
    }
    
    //LabelLetter doesn't need to draw directly.
    void draw(Renderer* /*renderer*/, const Mat4 & /*transform*/, uint32_t /*flags*/) override
    {
    }
    
private:
    bool _letterVisible;
};

Label* Label::create()
{
    auto ret = new (std::nothrow) Label;

    if (ret)
    {
        ret->autorelease();
    }

    return ret;
}

Label* Label::createWithSystemFont(const std::string& text, const std::string& font, float fontSize, const CSize& dimensions /* = CSize::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new (std::nothrow) Label(hAlignment,vAlignment);

    if (ret)
    {
        ret->setSystemFontName(font);
        ret->setSystemFontSize(fontSize);
        ret->setDimensions(dimensions.width, dimensions.height);
        ret->setString(text);

        ret->autorelease();

        return ret;
    }

    return nullptr;
}

Label* Label::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const CSize& dimensions /* = CSize::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new (std::nothrow) Label(hAlignment,vAlignment);

    if (ret && ret->initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

Label* Label::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment hAlignment /* = TextHAlignment::CENTER */, int maxLineWidth /* = 0 */)
{
    auto ret = new (std::nothrow) Label(hAlignment);

    if (ret && ret->initWithTTF(ttfConfig, text, hAlignment, maxLineWidth))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Label::initWithTTF(const std::string& text,
                        const std::string& fontFilePath, float fontSize,
                        const CSize& dimensions,
                        TextHAlignment /*hAlignment*/, TextVAlignment /*vAlignment*/)
{
    if (FileUtils::getInstance()->isFileExist(fontFilePath))
    {
        TTFConfig ttfConfig(fontFilePath, fontSize, CGlyphCollection::DYNAMIC);
        if (setTTFConfig(ttfConfig))
        {
            setDimensions(dimensions.width, dimensions.height);
            setString(text);
        }
        return true;
    }
    return false;
}

bool Label::initWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment /*hAlignment*/, int maxLineWidth)
{
    if (FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) && setTTFConfig(ttfConfig))
    {
        setMaxLineWidth(maxLineWidth);
        setString(text);
        return true;
    }
    return false;
}

Label::Label(TextHAlignment hAlignment /* = TextHAlignment::LEFT */, 
             TextVAlignment vAlignment /* = TextVAlignment::TOP */)
: _textSprite(nullptr)
, _shadowNode(nullptr)
, _fontAtlas(nullptr)
, _purgeTextureListener(nullptr)
, _reusedLetter(nullptr)
, _horizontalKernings(nullptr)
, _boldEnabled(false)
, _underlineNode(nullptr)
, _strikethroughEnabled(false)
{
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    reset();
    _hAlignment = hAlignment;
    _vAlignment = vAlignment;

#if CC_LABEL_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
}

Label::~Label()
{
    delete [] _horizontalKernings;

    if (_fontAtlas)
    {
        Node::removeAllChildrenWithCleanup(true);
        CC_SAFE_RELEASE_NULL(_reusedLetter);
        _batchNodes.clear();
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }
    // _eventDispatcher->removeEventListener(_purgeTextureListener);
    // _eventDispatcher->removeEventListener(_resetTextureListener);

    CC_SAFE_RELEASE_NULL(_textSprite);
    CC_SAFE_RELEASE_NULL(_shadowNode);
}

void Label::reset()
{
    CC_SAFE_RELEASE_NULL(_textSprite);
    CC_SAFE_RELEASE_NULL(_shadowNode);
    Node::removeAllChildrenWithCleanup(true);
    CC_SAFE_RELEASE_NULL(_reusedLetter);
    _letters.clear();
    _batchNodes.clear();
    _lettersInfo.clear();
    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = nullptr;
    }

    _currentLabelType = LabelType::STRING_TEXTURE;
    _currLabelEffect = LabelEffect::NORMAL;
    _contentDirty = false;
    _numberOfLines = 0;
    _lengthOfString = 0;
    _utf32Text.clear();
    _utf8Text.clear();

    TTFConfig temp;
    _fontConfig = temp;
    _outlineSize = 0.f;
    _systemFontDirty = false;
    _systemFont = "Helvetica";
    _systemFontSize = 12;

    if (_horizontalKernings)
    {
        delete[] _horizontalKernings;
        _horizontalKernings = nullptr;
    }
    _additionalKerning = 0.f;
    _lineHeight = 0.f;
    _lineSpacing = 0.f;
    _maxLineWidth = 0.f;
    _labelDimensions.width = 0.f;
    _labelDimensions.height = 0.f;
    _labelWidth = 0.f;
    _labelHeight = 0.f;
    _lineBreakWithoutSpaces = false;
    _hAlignment = TextHAlignment::LEFT;
    _vAlignment = TextVAlignment::TOP;

    _effectColorF = Color4F::BLACK;
    _textColor = Color4B::WHITE;
    _textColorF = Color4F::WHITE;
    setColor(Color3B::WHITE);

    _shadowDirty = false;
    _shadowEnabled = false;
    _shadowBlurRadius = 0.f;

    _uniformEffectColor = -1;
    _uniformEffectType = -1;
    _uniformTextColor = -1;

    _useDistanceField = false;
    _useA8Shader = false;
    _clipEnabled = false;
    _blendFuncDirty = false;
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    _isOpacityModifyRGB = false;
    _insideBounds = true;
    _enableWrap = true;
    _overflow = Overflow::NONE;
    _originalFontSize = 0.0f;
    _boldEnabled = false;
    if (_underlineNode)
    {
        removeChild(_underlineNode);
        _underlineNode = nullptr;
    }
    _strikethroughEnabled = false;
    setRotation(0.0f);        // reverse italics
}

//  ETC1 ALPHA supports
static Texture2D* _getTexture(Label* label)
{
    auto fontAtlas = label->getFontAtlas();
    Texture2D* texture = nullptr;
    if (fontAtlas != nullptr) {
        auto textures = fontAtlas->getTextures();
        if(!textures.empty()) {
            texture = textures.begin()->second;
        }
    }
    return texture;
}

void Label::updateShaderProgram()
{
    switch (_currLabelEffect)
    {
    case cocos2d::LabelEffect::NORMAL:
        if (_useDistanceField)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL));
        else if (_useA8Shader)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_NORMAL));
        else if (_shadowEnabled)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, _getTexture(this)));
        else
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, _getTexture(this)));

        break;
    case cocos2d::LabelEffect::OUTLINE: 
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_OUTLINE));
        _uniformEffectColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_effectColor");
        _uniformEffectType = glGetUniformLocation(getGLProgram()->getProgram(), "u_effectType");
        break;
    case cocos2d::LabelEffect::GLOW:
        if (_useDistanceField)
        {
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW));
            _uniformEffectColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_effectColor");
        }
        break;
    default:
        return;
    }
    
    _uniformTextColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_textColor");
}

void Label::setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled /* = false */, bool useA8Shader /* = false */)
{
    if(atlas)
    {
        _systemFontDirty = false;
    }

    if (atlas == _fontAtlas)
        return;

    CC_SAFE_RETAIN(atlas);
    if (_fontAtlas)
    {
        _batchNodes.clear();
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }
    _fontAtlas = atlas;
    
    if (_reusedLetter == nullptr)
    {
        _reusedLetter = Sprite::create();

		if (_reusedLetter != nullptr)
		{
			_reusedLetter->setOpacityModifyRGB(_isOpacityModifyRGB);
			_reusedLetter->retain();
			_reusedLetter->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		}
    }

    if (_fontAtlas)
    {
        _lineHeight = _fontAtlas->getLineHeight();
        _contentDirty = true;
        _systemFontDirty = false;
    }
    _useDistanceField = distanceFieldEnabled;
    _useA8Shader = useA8Shader;

    if (_currentLabelType != LabelType::TTF)
    {
        _currLabelEffect = LabelEffect::NORMAL;
        updateShaderProgram();
    }
}

bool Label::setTTFConfig(const TTFConfig& ttfConfig)
{
    _originalFontSize = ttfConfig.fontSize;
    return setTTFConfigInternal(ttfConfig);
}

void Label::setString(const std::string& text)
{
    if (text.compare(_utf8Text))
    {
        _utf8Text = text;
        _contentDirty = true;

        std::u32string utf32String;
        if (StringUtils::UTF8ToUTF32(_utf8Text, utf32String))
        {
            _utf32Text  = utf32String;
        }
    }
}

void Label::setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment)
{
    if (hAlignment != _hAlignment || vAlignment != _vAlignment)
    {
        _hAlignment = hAlignment;
        _vAlignment = vAlignment;

        _contentDirty = true;
    }
}

void Label::setMaxLineWidth(float maxLineWidth)
{
    if (_labelWidth == 0 && _maxLineWidth != maxLineWidth)
    {
        _maxLineWidth = maxLineWidth;
        _contentDirty = true;
    }
}

void Label::setDimensions(float width, float height)
{
    if(_overflow == Overflow::RESIZE_HEIGHT){
        height = 0;
    }
    if (height != _labelHeight || width != _labelWidth)
    {
        _labelWidth = width;
        _labelHeight = height;
        _labelDimensions.width = width;
        _labelDimensions.height = height;

        _maxLineWidth = width;
        _contentDirty = true;

        if(_overflow == Overflow::SHRINK){
            if (_originalFontSize > 0) {
                this->restoreFontSize();
            }
        }
    }
}

void Label::restoreFontSize()
{
    if(_currentLabelType == LabelType::TTF){
        auto ttfConfig = this->getTTFConfig();
        ttfConfig.fontSize = _originalFontSize;
        this->setTTFConfigInternal(ttfConfig);
    }else if(_currentLabelType == LabelType::STRING_TEXTURE){
        this->setSystemFontSize(_originalFontSize);
    }
}

void Label::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        _lineBreakWithoutSpaces = breakWithoutSpace;
        _contentDirty = true;     
    }
}

void Label::updateLabelLetters()
{
    if (!_letters.empty())
    {
        CRect uvRect;
        LabelLetter* letterSprite;
        int letterIndex;

        for (auto it = _letters.begin(); it != _letters.end();)
        {
            letterIndex = it->first;
            letterSprite = (LabelLetter*)it->second;

            if (letterIndex >= _lengthOfString)
            {
                Node::removeChild(letterSprite, true);
                it = _letters.erase(it);
            }
            else
            {
                auto& letterInfo = _lettersInfo[letterIndex];
                auto& letterDef = _fontAtlas->_letterDefinitions[letterInfo.utf32Char];
                uvRect.size.height = letterDef.height;
                uvRect.size.width = letterDef.width;
                uvRect.origin.x = letterDef.U;
                uvRect.origin.y = letterDef.V;

                auto batchNode = _batchNodes.at(letterDef.textureID);
                letterSprite->setTextureAtlas(batchNode->getTextureAtlas());
                letterSprite->setTexture(_fontAtlas->getTexture(letterDef.textureID));
                if (letterDef.width <= 0.f || letterDef.height <= 0.f)
                {
                    letterSprite->setTextureAtlas(nullptr);
                }
                else
                {
                    letterSprite->setTextureRect(uvRect, false, uvRect.size);
                    letterSprite->setTextureAtlas(_batchNodes.at(letterDef.textureID)->getTextureAtlas());
                    letterSprite->setAtlasIndex(_lettersInfo[letterIndex].atlasIndex);
                }

                auto px = letterInfo.positionX + letterDef.width / 2 + _linesOffsetX[letterInfo.lineIndex];
                auto py = letterInfo.positionY - letterDef.height / 2 + _letterOffsetY;
                letterSprite->setPosition(px, py);

                this->updateLetterSpriteScale(letterSprite);
                ++it;
            }
        }
    }
}

bool Label::alignText()
{
    if (_fontAtlas == nullptr || _utf32Text.empty())
    {
        setContentSize(CSize::ZERO);
        return true;
    }

    bool ret = true;
    do {
        _fontAtlas->prepareLetterDefinitions(_utf32Text);
        auto& textures = _fontAtlas->getTextures();
        auto size = textures.size();
        if (size > static_cast<size_t>(_batchNodes.size()))
        {
            for (auto index = static_cast<size_t>(_batchNodes.size()); index < size; ++index)
            {
                auto batchNode = SpriteBatchNode::createWithTexture(textures.at(index));
                if (batchNode)
                {
                    _isOpacityModifyRGB = batchNode->getTexture()->hasPremultipliedAlpha();
                    _blendFunc = batchNode->getBlendFunc();
                    batchNode->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                    batchNode->setPosition(Vec2::ZERO);
                    _batchNodes.pushBack(batchNode);
                }
            }
        }
        if (_batchNodes.empty())
        {
            return true;
        }
        // optimize for one-texture-only scenario
        // if multiple textures, then we should count how many chars
        // are per texture
        if (_batchNodes.size()==1)
            _batchNodes.at(0)->reserveCapacity(_utf32Text.size());

        _reusedLetter->setBatchNode(_batchNodes.at(0));
        
        _lengthOfString = 0;
        _textDesiredHeight = 0.f;
        _linesWidth.clear();
        if (_maxLineWidth > 0.f && !_lineBreakWithoutSpaces)
        {
            multilineTextWrapByWord();
        }
        else
        {
            multilineTextWrapByChar();
        }
        computeAlignmentOffset();

        if(_overflow == Overflow::SHRINK){
            float fontSize = this->getRenderingFontSize();

            if(fontSize > 0 &&  isVerticalClamp()){
                this->shrinkLabelToContentSize(CC_CALLBACK_0(Label::isVerticalClamp, this));
            }
        }

        if(!updateQuads()){
            ret = false;
            if(_overflow == Overflow::SHRINK){
                this->shrinkLabelToContentSize(CC_CALLBACK_0(Label::isHorizontalClamp, this));
            }
            break;
        }
    
        updateLabelLetters();
        
        updateColor();
    }while (0);

    return ret;
}

bool Label::computeHorizontalKernings(const std::u32string& stringToRender)
{
    if (_horizontalKernings)
    {
        delete [] _horizontalKernings;
        _horizontalKernings = nullptr;
    }

    int letterCount = 0;
    _horizontalKernings = _fontAtlas->getFont()->getHorizontalKerningForTextUTF32(stringToRender, letterCount);

    if(!_horizontalKernings)
        return false;
    else
        return true;
}

bool Label::isHorizontalClamped(float letterPositionX, int lineIndex)
{
    auto wordWidth = this->_linesWidth[lineIndex];
    bool letterOverClamp = (letterPositionX > _contentSize.width || letterPositionX < 0);
    if (!_enableWrap) {
        return letterOverClamp;
    }else{
        return (wordWidth > this->_contentSize.width && letterOverClamp);
    }
}

bool Label::updateQuads()
{
    bool ret = true;
    for (auto&& batchNode : _batchNodes)
    {
        batchNode->getTextureAtlas()->removeAllQuads();
    }
    
    for (int ctr = 0; ctr < _lengthOfString; ++ctr)
    {
        if (_lettersInfo[ctr].valid)
        {
            auto& letterDef = _fontAtlas->_letterDefinitions[_lettersInfo[ctr].utf32Char];
            
            _reusedRect.size.height = letterDef.height;
            _reusedRect.size.width  = letterDef.width;
            _reusedRect.origin.x    = letterDef.U;
            _reusedRect.origin.y    = letterDef.V;

            auto py = _lettersInfo[ctr].positionY + _letterOffsetY;
            if (_labelHeight > 0.f) {
                if (py > _tailoredTopY)
                {
                    auto clipTop = py - _tailoredTopY;
                    _reusedRect.origin.y += clipTop;
                    _reusedRect.size.height -= clipTop;
                    py -= clipTop;
                }

                // Zac: This causes text outside of scroll view to have the height zero'd out, which prevents a texture atlas from being assigned
                // This results in cursor breaking for text out of range, which sucks.
                // I suspect this was some optimization for off-screen text, but we don't use large amounts of text
                // so this optimization is not very helpful, and isn't implemented correctly anyways.
                /*
                if (py - letterDef.height < _tailoredBottomY)
                {
                    _reusedRect.size.height = (py < _tailoredBottomY) ? 0.f : (py - _tailoredBottomY);
                }*/
            }

            auto lineIndex = _lettersInfo[ctr].lineIndex;
            auto px = _lettersInfo[ctr].positionX + letterDef.width/2 + _linesOffsetX[lineIndex];

            if(_labelWidth > 0.f){
                if (this->isHorizontalClamped(px, lineIndex)) {
                    if(_overflow == Overflow::CLAMP){
                        _reusedRect.size.width = 0;
                    }else if(_overflow == Overflow::SHRINK){
                        if (_contentSize.width > letterDef.width) {
                            ret = false;
                            break;
                        }else{
                            _reusedRect.size.width = 0;
                        }

                    }
                }
            }


            if (_reusedRect.size.height > 0.f && _reusedRect.size.width > 0.f)
            {
                _reusedLetter->setTextureRect(_reusedRect, false, _reusedRect.size);
                float letterPositionX = _lettersInfo[ctr].positionX + _linesOffsetX[_lettersInfo[ctr].lineIndex];
                _reusedLetter->setPosition(letterPositionX, py);
                auto index = static_cast<int>(_batchNodes.at(letterDef.textureID)->getTextureAtlas()->getTotalQuads());
                _lettersInfo[ctr].atlasIndex = index;

                this->updateLetterSpriteScale(_reusedLetter);

                _batchNodes.at(letterDef.textureID)->insertQuadFromSprite(_reusedLetter, index);
            }
        }     
    }


    return ret;
}

bool Label::setTTFConfigInternal(const TTFConfig& ttfConfig)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasTTF(&ttfConfig);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::TTF;
    setFontAtlas(newAtlas,ttfConfig.distanceFieldEnabled,true);

    _fontConfig = ttfConfig;

    if (_fontConfig.outlineSize > 0)
    {
        _fontConfig.distanceFieldEnabled = false;
        _useDistanceField = false;
        _useA8Shader = false;
        _currLabelEffect = LabelEffect::OUTLINE;
        updateShaderProgram();
    }
    else
    {
        _currLabelEffect = LabelEffect::NORMAL;
        updateShaderProgram();
    }

    if (_fontConfig.italics)
        this->enableItalics();
    if (_fontConfig.bold)
        this->enableBold();
    if (_fontConfig.underline)
        this->enableUnderline();
    if (_fontConfig.strikethrough)
        this->enableStrikethrough();

    return true;
}

void Label::scaleFontSizeDown(float fontSize)
{
    bool shouldUpdateContent = true;
    if(_currentLabelType == LabelType::TTF){
        auto ttfConfig = this->getTTFConfig();
        ttfConfig.fontSize = fontSize;
        this->setTTFConfigInternal(ttfConfig);
    }else if (_currentLabelType == LabelType::STRING_TEXTURE){
        this->setSystemFontSize(fontSize);
    }
    
    if (shouldUpdateContent) {
        this->updateContent();
    }
}

void Label::enableGlow(const Color4B& glowColor)
{
    if (_currentLabelType == LabelType::TTF)
    {
        if (_fontConfig.distanceFieldEnabled == false)
        {
            auto config = _fontConfig;
            config.outlineSize = 0;
            config.distanceFieldEnabled = true;
            setTTFConfig(config);
            _contentDirty = true;
        }
        _currLabelEffect = LabelEffect::GLOW;
        _effectColorF.r = glowColor.r / 255.0f;
        _effectColorF.g = glowColor.g / 255.0f;
        _effectColorF.b = glowColor.b / 255.0f;
        _effectColorF.a = glowColor.a / 255.0f;
        updateShaderProgram();
    }
}

void Label::enableOutline(const Color4B& outlineColor,int outlineSize /* = -1 */)
{
    CCASSERT(_currentLabelType == LabelType::STRING_TEXTURE || _currentLabelType == LabelType::TTF, "Only supported system font and TTF!");

    if (outlineSize > 0 || _currLabelEffect == LabelEffect::OUTLINE)
    {
        if (_currentLabelType == LabelType::TTF)
        {
            _effectColorF.r = outlineColor.r / 255.0f;
            _effectColorF.g = outlineColor.g / 255.0f;
            _effectColorF.b = outlineColor.b / 255.0f;
            _effectColorF.a = outlineColor.a / 255.0f;

            if (outlineSize > 0 && _fontConfig.outlineSize != outlineSize)
            {
                _fontConfig.outlineSize = outlineSize;
                setTTFConfig(_fontConfig);
            }
        }
        else if (_effectColorF != outlineColor || _outlineSize != outlineSize)
        {
            _effectColorF.r = outlineColor.r / 255.f;
            _effectColorF.g = outlineColor.g / 255.f;
            _effectColorF.b = outlineColor.b / 255.f;
            _effectColorF.a = outlineColor.a / 255.f;
            _currLabelEffect = LabelEffect::OUTLINE;
            _contentDirty = true;
        }
        _outlineSize = outlineSize;
    }
}

void Label::enableShadow(const Color4B& shadowColor /* = Color4B::BLACK */,
                         const CSize &offset /* = CSize(2 ,-2)*/,
                         int /* blurRadius = 0 */)
{
    _shadowEnabled = true;
    _shadowDirty = true;

    _shadowOffset.width = offset.width;
    _shadowOffset.height = offset.height;
    //TODO: support blur for shadow

    _shadowColor3B.r = shadowColor.r;
    _shadowColor3B.g = shadowColor.g;
    _shadowColor3B.b = shadowColor.b;
    _shadowOpacity = shadowColor.a;

    if (!_systemFontDirty && !_contentDirty && _textSprite)
    {
        auto fontDef = _getFontDefinition();
        if (_shadowNode)
        {
            if (shadowColor != _shadowColor4F)
            {
                _shadowNode->release();
                _shadowNode = nullptr;
                createShadowSpriteForSystemFont(fontDef);
            }
            else
            {
                _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);
            }
        }
        else
        {
            createShadowSpriteForSystemFont(fontDef);
        }
    }

    _shadowColor4F.r = shadowColor.r / 255.0f;
    _shadowColor4F.g = shadowColor.g / 255.0f;
    _shadowColor4F.b = shadowColor.b / 255.0f;
    _shadowColor4F.a = shadowColor.a / 255.0f;
}

void Label::enableItalics()
{
    // Disabled
}

void Label::enableBold()
{
    if (!_boldEnabled)
    {
        // bold is implemented with outline
        enableShadow(Color4B::WHITE, CSize(0.9f, 0), 0);
        // add one to kerning
        setAdditionalKerning(_additionalKerning+1);
        _boldEnabled = true;
    }
}

void Label::enableUnderline()
{
    // remove it, just in case to prevent adding two or more
    if (!_underlineNode)
    {
        _underlineNode = DrawNode::create();
        addChild(_underlineNode, 100000);
        _contentDirty = true;
    }
}

void Label::enableStrikethrough()
{
    if (!_strikethroughEnabled)
    {
        enableUnderline();
        _strikethroughEnabled = true;
    }
}

void Label::disableEffect()
{
    disableEffect(LabelEffect::ALL);
}

void Label::disableEffect(LabelEffect effect)
{
    switch (effect)
    {
        case cocos2d::LabelEffect::NORMAL:
            break;
        case cocos2d::LabelEffect::OUTLINE:
            if (_currLabelEffect == LabelEffect::OUTLINE)
            {
                if (_currentLabelType == LabelType::TTF)
                {
                    _fontConfig.outlineSize = 0;
                    setTTFConfig(_fontConfig);
                }
                _currLabelEffect = LabelEffect::NORMAL;
                _contentDirty = true;
            }
            break;
        case cocos2d::LabelEffect::SHADOW:
            if (_shadowEnabled)
            {
                _shadowEnabled = false;
                CC_SAFE_RELEASE_NULL(_shadowNode);
                updateShaderProgram();
            }
            break;
        case cocos2d::LabelEffect::GLOW:
            if (_currLabelEffect == LabelEffect::GLOW)
            {
                _currLabelEffect = LabelEffect::NORMAL;
                updateShaderProgram();
            }
            break;
        case cocos2d::LabelEffect::ITALICS:
            setRotation(0.0f);
            break;
        case cocos2d::LabelEffect::BOLD:
            if (_boldEnabled) {
                _boldEnabled = false;
                _additionalKerning -= 1;
                disableEffect(LabelEffect::SHADOW);
            }
            break;
        case cocos2d::LabelEffect::UNDERLINE:
            if (_underlineNode) {
                removeChild(_underlineNode);
                _underlineNode = nullptr;
            }
            break;
        case cocos2d::LabelEffect::STRIKETHROUGH:
            _strikethroughEnabled = false;
            // since it is based on underline, disable it as well
            disableEffect(LabelEffect::UNDERLINE);
            break;
        case LabelEffect::ALL:
        {
            disableEffect(LabelEffect::SHADOW);
            disableEffect(LabelEffect::GLOW);
            disableEffect(LabelEffect::OUTLINE);
            disableEffect(LabelEffect::ITALICS);
            disableEffect(LabelEffect::BOLD);
            disableEffect(LabelEffect::UNDERLINE);
            disableEffect(LabelEffect::STRIKETHROUGH);
        }
            break;
        default:
            break;
    }
}

void Label::createSpriteForSystemFont(const FontDefinition& fontDef)
{
    _currentLabelType = LabelType::STRING_TEXTURE;

    auto texture = new (std::nothrow) Texture2D;
    // texture->initWithString(_utf8Text.c_str(), fontDef);

    _textSprite = Sprite::createWithTexture(texture);
    _textSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->setContentSize(_textSprite->getContentSize());
    texture->release();
    if (_blendFuncDirty)
    {
        _textSprite->setBlendFunc(_blendFunc);
    }

    _textSprite->retain();
    _textSprite->updateDisplayedColor(_displayedColor);
    _textSprite->updateDisplayedOpacity(_displayedOpacity);
}

void Label::createShadowSpriteForSystemFont(const FontDefinition& fontDef)
{
    if (!fontDef._stroke._strokeEnabled && fontDef._fontFillColor == _shadowColor3B
        && (fontDef._fontAlpha == _shadowOpacity))
    {
        _shadowNode = Sprite::createWithTexture(_textSprite->getTexture());
    }
    else
    {
        FontDefinition shadowFontDefinition = fontDef;
        shadowFontDefinition._fontFillColor.r = _shadowColor3B.r;
        shadowFontDefinition._fontFillColor.g = _shadowColor3B.g;
        shadowFontDefinition._fontFillColor.b = _shadowColor3B.b;
        shadowFontDefinition._fontAlpha = _shadowOpacity;

        shadowFontDefinition._stroke._strokeColor = shadowFontDefinition._fontFillColor;
        shadowFontDefinition._stroke._strokeAlpha = shadowFontDefinition._fontAlpha;

        auto texture = new (std::nothrow) Texture2D;
        // texture->initWithString(_utf8Text.c_str(), shadowFontDefinition);
        _shadowNode = Sprite::createWithTexture(texture);
        texture->release();
    }

    if (_shadowNode)
    {
        if (_blendFuncDirty)
        {
            _shadowNode->setBlendFunc(_blendFunc);
        }

        _shadowNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);

        _shadowNode->retain();
        _shadowNode->updateDisplayedColor(_displayedColor);
        _shadowNode->updateDisplayedOpacity(_displayedOpacity);
    }
}

void Label::updateContent()
{
    if (_systemFontDirty)
    {
        if (_fontAtlas)
        {
            _batchNodes.clear();

            FontAtlasCache::releaseFontAtlas(_fontAtlas);
            _fontAtlas = nullptr;
        }

        _systemFontDirty = false;
    }

    CC_SAFE_RELEASE_NULL(_textSprite);
    CC_SAFE_RELEASE_NULL(_shadowNode);
    bool updateFinished = true;

    if (_fontAtlas)
    {
        std::u32string utf32String;
        if (StringUtils::UTF8ToUTF32(_utf8Text, utf32String))
        {
            _utf32Text = utf32String;
        }

        computeHorizontalKernings(_utf32Text);
        updateFinished = alignText();
    }
    else
    {
        auto fontDef = _getFontDefinition();
        createSpriteForSystemFont(fontDef);
        if (_shadowEnabled)
        {
            createShadowSpriteForSystemFont(fontDef);
        }
    }

    if (_underlineNode)
    {
        _underlineNode->clear();

        if (_numberOfLines)
        {
            // This is the logic for TTF fonts
            const float charheight = (_textDesiredHeight / _numberOfLines);
            _underlineNode->setLineWidth(charheight/6);

            // atlas font
            for (int i=0; i<_numberOfLines; ++i)
            {
                float offsety = 0;
                if (_strikethroughEnabled)
                    offsety += charheight / 2;
                // FIXME: Might not work with different vertical alignments
                float y = (_numberOfLines - i - 1) * charheight + offsety;

                // Github issue #15214. Uses _displayedColor instead of _textColor for the underline.
                // This is to have the same behavior of SystemFonts.
                _underlineNode->drawLine(Vec2(_linesOffsetX[i],y), Vec2(_linesWidth[i] + _linesOffsetX[i],y), Color4F(_displayedColor));
            }
        }
        else if (_textSprite)
        {
            // ...and is the logic for System fonts
            float y = 0;
            const auto spriteSize = _textSprite->getContentSize();
            _underlineNode->setLineWidth(spriteSize.height/6);

            if (_strikethroughEnabled)
                // FIXME: system fonts don't report the height of the font correctly. only the size of the texture, which is POT
                y += spriteSize.height / 2;
            // FIXME: Might not work with different vertical alignments
            _underlineNode->drawLine(Vec2(0,y), Vec2(spriteSize.width,y), Color4F(_textSprite->getDisplayedColor()));
        }
    }

    if(updateFinished){
        _contentDirty = false;
    }

#if CC_LABEL_DEBUG_DRAW
    _debugDrawNode->clear();
    Vec2 vertices[4] =
    {
        Vec2::ZERO,
        Vec2(_contentSize.width, 0),
        Vec2(_contentSize.width, _contentSize.height),
        Vec2(0, _contentSize.height)
    };
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F::WHITE);
#endif
}

void Label::onDrawShadow(GLProgram* glProgram, const Color4F& shadowColor)
{
    if (_currentLabelType == LabelType::TTF)
    {
        if (_currLabelEffect == LabelEffect::OUTLINE)
        {
            glProgram->setUniformLocationWith1i(_uniformEffectType, 2); // 2: shadow
            glProgram->setUniformLocationWith4f(_uniformEffectColor, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
        }
        else
        {
            glProgram->setUniformLocationWith4f(_uniformTextColor, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
            if (_currLabelEffect == LabelEffect::GLOW)
            {
                glProgram->setUniformLocationWith4f(_uniformEffectColor, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
            }
        }

        glProgram->setUniformsForBuiltins(_shadowTransform);
        for (auto&& it : _letters)
        {
            it.second->updateTransform();
        }
        for (auto&& batchNode : _batchNodes)
        {
            batchNode->getTextureAtlas()->drawQuads();
        }
    }
    else
    {
        Color3B oldColor = _realColor;
        GLubyte oldOPacity = _displayedOpacity;
        _displayedOpacity = shadowColor.a * 255;
        setColor(Color3B(shadowColor));

        glProgram->setUniformsForBuiltins(_shadowTransform);
        for (auto&& it : _letters)
        {
            it.second->updateTransform();
        }
        for (auto&& batchNode : _batchNodes)
        {
            batchNode->getTextureAtlas()->drawQuads();
        }

        _displayedOpacity = oldOPacity;
        setColor(oldColor);
    }
}

void Label::onDraw(const Mat4& transform, bool /*transformUpdated*/)
{
    auto glprogram = getGLProgram();
    glprogram->use();
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    if (_shadowEnabled)
    {
        if (_boldEnabled)
            onDrawShadow(glprogram, _textColorF);
        else
            onDrawShadow(glprogram, _shadowColor4F);
    }

    glprogram->setUniformsForBuiltins(transform);
    for (auto&& it : _letters)
    {
        it.second->updateTransform();
    }

    if (_currentLabelType == LabelType::TTF)
    {
        switch (_currLabelEffect) {
        case LabelEffect::OUTLINE:
            // draw outline of text
            glprogram->setUniformLocationWith1i(_uniformEffectType, 1); // 1: outline
            glprogram->setUniformLocationWith4f(_uniformEffectColor,
                _effectColorF.r, _effectColorF.g, _effectColorF.b, _effectColorF.a);
            for (auto&& batchNode : _batchNodes)
            {
                batchNode->getTextureAtlas()->drawQuads();
            }

            // draw text without outline
            glprogram->setUniformLocationWith1i(_uniformEffectType, 0); // 0: text
            glprogram->setUniformLocationWith4f(_uniformTextColor, _textColorF.r, _textColorF.g, _textColorF.b, _textColorF.a);
            break;
        case LabelEffect::GLOW:
            glprogram->setUniformLocationWith4f(_uniformEffectColor,
                _effectColorF.r, _effectColorF.g, _effectColorF.b, _effectColorF.a);
        case LabelEffect::NORMAL:
            glprogram->setUniformLocationWith4f(_uniformTextColor,
                _textColorF.r, _textColorF.g, _textColorF.b, _textColorF.a);
            break;
        default:
            break;
        }
    }

    for (auto&& batchNode : _batchNodes)
    {
        batchNode->getTextureAtlas()->drawQuads();
    }
}

void Label::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_batchNodes.empty() || _lengthOfString <= 0)
    {
        return;
    }
    // Don't do calculate the culling if the transform was not updated
    bool transformUpdated = flags & FLAGS_TRANSFORM_DIRTY;
    {
        _customCommand.init(0.0f, transform, flags);
        _customCommand.func = CC_CALLBACK_0(Label::onDraw, this, transform, transformUpdated);

        renderer->addCommand(&_customCommand);
    }
}

void Label::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    _selfFlags |= parentFlags;

    if (! _visible || (_utf8Text.empty() && _children.empty()) )
    {
        return;
    }
    
    if (_systemFontDirty || _contentDirty)
    {
        updateContent();
    }
    
    if(_selfFlags & FLAGS_DIRTY_MASK)
    {
        _modelViewTransform = parentTransform * getNodeToParentTransform();
    }

    if (_shadowEnabled && (_shadowDirty || (_selfFlags & FLAGS_DIRTY_MASK)) && !_utf8Text.empty())
    {
        _position.x += _shadowOffset.width;
        _position.y += _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowTransform = parentTransform * getNodeToParentTransform();

        _position.x -= _shadowOffset.width;
        _position.y -= _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowDirty = false;
    }

    // self draw
    this->drawSelf(true, renderer, _selfFlags);

    for (int index = 0; index < _children.size(); index++)
    {
        _children[index]->visit(renderer, _modelViewTransform, _selfFlags);
    }

    _selfFlags = 0;
}

void Label::drawSelf(bool visibleByCamera, Renderer* renderer, uint32_t flags)
{
    if (_textSprite)
    {
        if (_shadowNode)
        {
            _shadowNode->visit(renderer, _modelViewTransform, flags);
        }
        _textSprite->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera && !_utf8Text.empty())
    {
        draw(renderer, _modelViewTransform, flags);
    }
}

void Label::setSystemFontName(const std::string& systemFont)
{
    if (systemFont != _systemFont)
    {
        _systemFont = systemFont;
        _currentLabelType = LabelType::STRING_TEXTURE;
        _systemFontDirty = true;
    }
}

void Label::setSystemFontSize(float fontSize)
{
    if (_systemFontSize != fontSize)
    {
        _systemFontSize = fontSize;
        _originalFontSize = fontSize;
        _currentLabelType = LabelType::STRING_TEXTURE;
        _systemFontDirty = true;
    }
}

///// PROTOCOL STUFF
Sprite* Label::getLetter(int letterIndex, bool applyCursorOffset, bool offsetUnicodeCombines)
{
    if (_systemFontDirty || _currentLabelType == LabelType::STRING_TEXTURE)
    {
        return nullptr;
    }

    auto contentDirty = _contentDirty;

    if (contentDirty)
    {
        updateContent();
    }

    if (!(_textSprite == nullptr && letterIndex < _lengthOfString))
    {
        return nullptr;
    }

    const auto &letterInfo = _lettersInfo[letterIndex];

    if (!letterInfo.valid || letterInfo.atlasIndex < 0)
    {
        return nullptr;
    }

    Sprite* letter = nullptr;

    if (_letters.find(letterIndex) != _letters.end())
    {
        letter = _letters[letterIndex];
    }

    if (letter == nullptr)
    {
        const auto& letterDef = _fontAtlas->_letterDefinitions[letterInfo.utf32Char];
        auto textureID = letterDef.textureID;
        CRect uvRect;
        uvRect.size.height = letterDef.height;
        uvRect.size.width = letterDef.width;
        uvRect.origin.x = letterDef.U;
        uvRect.origin.y = letterDef.V;

        if (letterDef.width <= 0.f || letterDef.height <= 0.f)
        {
            return LabelLetter::create();
        }

        letter = LabelLetter::createWithTexture(_fontAtlas->getTexture(textureID), uvRect);
        letter->setTextureAtlas(_batchNodes.at(textureID)->getTextureAtlas());
        letter->setAtlasIndex(letterInfo.atlasIndex);

        int preceedingNormalLetterCount = 0;

        for (int seekIndex = letterIndex; seekIndex >= 0; seekIndex--)
        {
            const auto &letterInfoSeek = _lettersInfo[seekIndex];

            preceedingNormalLetterCount += StringUtils::isUnicodeCombine(letterInfoSeek.utf32Char) ? 0 : 1;
        }

        // Tag letters with their index
        letter->setSpriteTag(preceedingNormalLetterCount);

        float px = 0.0f;
        float py = 0.0f;

        if (!offsetUnicodeCombines || !StringUtils::isUnicodeCombine(letterInfo.utf32Char))
        {
            px = letterInfo.positionX + (applyCursorOffset ? 0.0f : uvRect.size.width / 2.0f) + _linesOffsetX[letterInfo.lineIndex];
            py = letterInfo.positionY - uvRect.size.height / 2.0f + _letterOffsetY;
        }
        else
        {
            int seekIndex = letterIndex;
            bool isPositive = ((_lettersInfo[seekIndex].positionY + _letterOffsetY / 2.0f) >= 0.0f);
            bool isPrioNormalLetter = true;
            
            do
            {
                const auto &letterInfoSeek = _lettersInfo[seekIndex];
                float offset = letterInfoSeek.positionY + _letterOffsetY / 2.0f;
                const auto& letterDefSeek = _fontAtlas->_letterDefinitions[letterInfoSeek.utf32Char];

                isPrioNormalLetter = (seekIndex <= 0 || !StringUtils::isUnicodeCombine(_lettersInfo[seekIndex - 1].utf32Char));

                if ((isPositive && offset >= 0.0f) || (!isPositive && offset <= 0.0f))
                {
                    if (!isPrioNormalLetter)
                    {
                        offset += (isPositive ? -letterDefSeek.height / 2.0f : letterDefSeek.height / 2.0f);
                    }

                    py += offset;
                }

                if (--seekIndex < 0)
                {
                    break;
                }

            } while (StringUtils::isUnicodeCombine(_lettersInfo[seekIndex].utf32Char));

            if (seekIndex >= 0 && seekIndex < int(_lettersInfo.size()))
            {
                const auto &letterInfoSeek = _lettersInfo[seekIndex];

                if (_fontAtlas->_letterDefinitions.find(letterInfoSeek.utf32Char) != _fontAtlas->_letterDefinitions.end())
                {
                    const auto& letterDefSeek = _fontAtlas->_letterDefinitions[letterInfoSeek.utf32Char];
                    CRect uvRectSeek;
                    uvRectSeek.size.height = letterDefSeek.height;
                    uvRectSeek.size.width = letterDefSeek.width;
                    uvRectSeek.origin.x = letterDefSeek.U;
                    uvRectSeek.origin.y = letterDefSeek.V;

                    if (letterInfoSeek.lineIndex >= 0 && letterInfoSeek.lineIndex < int(_linesOffsetX.size()))
                    {
                        px += letterInfoSeek.positionX + (applyCursorOffset ? 0.0f : uvRectSeek.size.width / 2) + _linesOffsetX[letterInfoSeek.lineIndex];
                    }
                    py += letterInfoSeek.positionY - uvRectSeek.size.height / 2 + _letterOffsetY;
                }
            }
            else
            {
                if (letterInfo.lineIndex >= 0 && letterInfo.lineIndex < int(_linesOffsetX.size()))
                {
                    px += letterInfo.positionX + (applyCursorOffset ? 0.0f : uvRect.size.width / 2) + _linesOffsetX[letterInfo.lineIndex];
                }
                py += letterInfo.positionY - uvRect.size.height / 2 + _letterOffsetY;
            }
        }

        letter->setPosition(px, py);
        letter->setOpacity(_realOpacity);
        
        addChild(letter);
        _letters[letterIndex] = letter;
    }

    return letter;
}

void Label::setLineHeight(float height)
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");

    if (_lineHeight != height)
    {
        _lineHeight = height;
        _contentDirty = true;
    }
}

float Label::getLineHeight() const
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");
    return _textSprite ? 0.0f : _lineHeight;
}

void Label::setLineSpacing(float height)
{
    if (_lineSpacing != height)
    {
        _lineSpacing = height;
        _contentDirty = true;
    }
}

float Label::getLineSpacing() const
{
    return _lineSpacing;
}

void Label::setAdditionalKerning(float space)
{

    if (_currentLabelType != LabelType::STRING_TEXTURE)
    {
        if (_additionalKerning != space)
        {
            _additionalKerning = space;
            _contentDirty = true;
        }
    }
    else
        CCLOG("Label::setAdditionalKerning not supported on LabelType::STRING_TEXTURE");
}

float Label::getAdditionalKerning() const
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");

    return _additionalKerning;
}

void Label::computeStringNumLines()
{
    int quantityOfLines = 1;

    if (_utf32Text.empty())
    {
        _numberOfLines = 0;
        return;
    }

    // count number of lines
    size_t stringLen = _utf32Text.length();
    for (size_t i = 0; i < stringLen - 1; ++i)
    {
        if (_utf32Text[i] == (char32_t)TextFormatter::NewLine)
        {
            quantityOfLines++;
        }
    }

    _numberOfLines = quantityOfLines;
}

int Label::getStringNumLines()
{
    if (_contentDirty)
    {
        updateContent();
    }

    if (_currentLabelType == LabelType::STRING_TEXTURE)
    {
        computeStringNumLines();
    }

    return _numberOfLines;
}

int Label::getStringLength()
{
    _lengthOfString = static_cast<int>(_utf32Text.length());
    return _lengthOfString;
}

int Label::getUnicodeStringLength()
{
    int totalLength = this->getStringLength();
    int unicodeLength = 0;

    for (int letterIndex = 0; letterIndex < totalLength; letterIndex++)
    {
        const auto &letterInfo = _lettersInfo[letterIndex];

        unicodeLength += StringUtils::isUnicodeCombine(letterInfo.utf32Char) ? 0 : 1;
    }

    return unicodeLength;
}

// RGBA protocol
void Label::setOpacityModifyRGB(bool isOpacityModifyRGB)
{
    if (isOpacityModifyRGB != _isOpacityModifyRGB)
    {
        _isOpacityModifyRGB = isOpacityModifyRGB;
        updateColor();
    }
}

void Label::updateDisplayedColor(const Color3B& parentColor)
{
    Node::updateDisplayedColor(parentColor);

    if (_textSprite)
    {
        _textSprite->updateDisplayedColor(_displayedColor);
    }

    if (_shadowNode)
    {
        _shadowNode->updateDisplayedColor(_displayedColor);
    }

    if (_underlineNode)
    {
        // FIXME: _underlineNode is not a sprite/label. It is a DrawNode
        // and updating its color doesn't work. it must be re-drawn,
        // which makes it super expensive to change update it frequently
        // Correct solution is to update the DrawNode directly since we know it is
        // a line. Returning a pointer to the line is an option
        _contentDirty = true;
    }

    for (auto&& it : _letters)
    {
        it.second->updateDisplayedColor(_displayedColor);
    }
}

void Label::updateDisplayedOpacity(GLubyte parentOpacity)
{
    Node::updateDisplayedOpacity(parentOpacity);

    if (_textSprite)
    {
        _textSprite->updateDisplayedOpacity(_displayedOpacity);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedOpacity(_displayedOpacity);
        }
    }

    for (auto&& it : _letters)
    {
        it.second->updateDisplayedOpacity(_displayedOpacity);
    }
}

// FIXME: it is not clear what is the difference between setTextColor() and setColor()
// if setTextColor() only changes the text and nothing but the text (no glow, no outline, not underline)
// that's fine but it should be documented
void Label::setTextColor(const Color4B &color)
{
    CCASSERT(_currentLabelType == LabelType::TTF || _currentLabelType == LabelType::STRING_TEXTURE, "Only supported system font and ttf!");

    if (_currentLabelType == LabelType::STRING_TEXTURE && _textColor != color)
    {
        _contentDirty = true;
    }

    _textColor = color;
    _textColorF.r = _textColor.r / 255.0f;
    _textColorF.g = _textColor.g / 255.0f;
    _textColorF.b = _textColor.b / 255.0f;
    _textColorF.a = _textColor.a / 255.0f;
}

void Label::updateColor()
{
    if (_batchNodes.empty())
    {
        return;
    }

    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }

    cocos2d::TextureAtlas* textureAtlas;
    V3F_C4B_T2F_Quad *quads;
    for (auto&& batchNode:_batchNodes)
    {
        textureAtlas = batchNode->getTextureAtlas();
        quads = textureAtlas->getQuads();
        auto count = textureAtlas->getTotalQuads();

        for (int index = 0; index < count; ++index)
        {
            quads[index].bl.colors = color4;
            quads[index].br.colors = color4;
            quads[index].tl.colors = color4;
            quads[index].tr.colors = color4;
            textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

std::string Label::getDescription() const
{
    char tmp[50];
    sprintf(tmp, "<Label | Tag = %d, Label = >", -1);
    std::string ret = tmp;
    ret += _utf8Text;

    return ret;
}

const CSize& Label::getContentSize() const
{
    if (_systemFontDirty || _contentDirty)
    {
        const_cast<Label*>(this)->updateContent();
    }
    return _contentSize;
}

CRect Label::getBoundingBox() const
{
    const_cast<Label*>(this)->getContentSize();

    return Node::getBoundingBox();
}

void Label::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
    _blendFuncDirty = true;
    if (_textSprite)
    {
        _textSprite->setBlendFunc(blendFunc);
        if (_shadowNode)
        {
            _shadowNode->setBlendFunc(blendFunc);
        }
    }
}

void Label::removeLetters()
{
	std::vector<Sprite*> toRemove = std::vector<Sprite*>();
	Vector<Node*> children = this->getChildren();

	for (auto it = this->_letters.begin(); it != this->_letters.end(); it++)
	{
		if (children.find(it->second) != children.end())
		{
			toRemove.push_back(it->second);
		}
	}

	for (auto it = toRemove.begin(); it != toRemove.end(); it++)
	{
		this->removeChild(*it);
	}

	_letters.clear();
}

void Label::removeAllChildrenWithCleanup(bool cleanup)
{
    Node::removeAllChildrenWithCleanup(cleanup);
    _letters.clear();
}

void Label::removeChild(Node* child, bool cleanup /* = true */)
{
    Node::removeChild(child, cleanup);
    for (auto&& it : _letters)
    {
        if (it.second == child)
        {
            _letters.erase(it.first);
            break;
        }
    }
}

FontDefinition Label::_getFontDefinition() const
{
    FontDefinition systemFontDef;
    systemFontDef._fontName = _systemFont;
    systemFontDef._fontSize = _systemFontSize;
    systemFontDef._alignment = _hAlignment;
    systemFontDef._vertAlignment = _vAlignment;
    systemFontDef._dimensions.width = _labelWidth;
    systemFontDef._dimensions.height = _labelHeight;
    systemFontDef._fontFillColor.r = _textColor.r;
    systemFontDef._fontFillColor.g = _textColor.g;
    systemFontDef._fontFillColor.b = _textColor.b;
    systemFontDef._fontAlpha = _textColor.a;
    systemFontDef._shadow._shadowEnabled = false;
    systemFontDef._enableWrap = _enableWrap;
    systemFontDef._overflow = (int)_overflow;

    if (_currLabelEffect == LabelEffect::OUTLINE && _outlineSize > 0.f)
    {
        systemFontDef._stroke._strokeEnabled = true;
        systemFontDef._stroke._strokeSize = _outlineSize;
        systemFontDef._stroke._strokeColor.r = _effectColorF.r * 255;
        systemFontDef._stroke._strokeColor.g = _effectColorF.g * 255;
        systemFontDef._stroke._strokeColor.b = _effectColorF.b * 255;
        systemFontDef._stroke._strokeAlpha = _effectColorF.a * 255;
    }
    else
    {
        systemFontDef._stroke._strokeEnabled = false;
    }

    if (systemFontDef._stroke._strokeEnabled)
    {
        CCLOGERROR("Stroke Currently only supported on iOS and Android!");
        systemFontDef._stroke._strokeEnabled = false;
    }

    return systemFontDef;
}

float Label::getRenderingFontSize()const
{
    float fontSize;
    if(_currentLabelType == LabelType::TTF){
        fontSize = this->getTTFConfig().fontSize;
    }else if(_currentLabelType == LabelType::STRING_TEXTURE){
        fontSize = _systemFontSize;
    }else{ //FIXME: find a way to calculate char map font size
        fontSize = this->getLineHeight();
    }
    return fontSize;
}

void Label::enableWrap(bool enable)
{
    if(enable == _enableWrap || _overflow == Overflow::RESIZE_HEIGHT){
        return;
    }

    this->_enableWrap = enable;
   
    this->rescaleWithOriginalFontSize();
    
    _contentDirty = true;
}

bool Label::isWrapEnabled()const
{
    return this->_enableWrap;
}

void Label::setOverflow(Overflow overflow)
{
    if(_overflow == overflow){
        return;
    }

    if(overflow == Overflow::RESIZE_HEIGHT){
        this->setDimensions(_labelDimensions.width,0);
        this->enableWrap(true);
    }
    _overflow = overflow;
    
    this->rescaleWithOriginalFontSize();
    
    _contentDirty = true;
}

void Label::rescaleWithOriginalFontSize()
{
    auto renderingFontSize = this->getRenderingFontSize();
    if (_originalFontSize - renderingFontSize >= 1) {
        this->scaleFontSizeDown(_originalFontSize);
    }
}

Label::Overflow Label::getOverflow()const
{
    return _overflow;
}

void Label::updateLetterSpriteScale(Sprite* sprite)
{
    sprite->setScale(1.0f);
}

void Label::computeAlignmentOffset()
{
    _linesOffsetX.clear();
    switch (_hAlignment)
    {
    case cocos2d::TextHAlignment::LEFT:
        _linesOffsetX.assign(_numberOfLines, 0);
        break;
    case cocos2d::TextHAlignment::CENTER:
        for (auto lineWidth : _linesWidth)
        {
            _linesOffsetX.push_back((_contentSize.width - lineWidth) / 2.f);
        }
        break;
    case cocos2d::TextHAlignment::RIGHT:
        for (auto lineWidth : _linesWidth)
        {
            _linesOffsetX.push_back(_contentSize.width - lineWidth);
        }
        break;
    default:
        break;
    }

    switch (_vAlignment)
    {
    case cocos2d::TextVAlignment::TOP:
        _letterOffsetY = _contentSize.height;
        break;
    case cocos2d::TextVAlignment::CENTER:
        _letterOffsetY = (_contentSize.height + _textDesiredHeight) / 2.f;
        break;
    case cocos2d::TextVAlignment::BOTTOM:
        _letterOffsetY = _textDesiredHeight;
        break;
    default:
        break;
    }
}

int Label::getFirstCharLen(const std::u32string& /*utf32Text*/, int /*startIndex*/, int /*textLen*/)
{
    return 1;
}

int Label::getFirstWordLen(const std::u32string& utf32Text, int startIndex, int textLen)
{
    auto character = utf32Text[startIndex];
    if (StringUtils::isCJKUnicode(character) || StringUtils::isUnicodeSpace(character) || character == (char32_t)TextFormatter::NewLine)
    {
        return 1;
    }

    int len = 1;
    FontLetterDefinition letterDef;
    if (!_fontAtlas->getLetterDefinitionForChar(character, letterDef)) {
        return len;
    }
    auto nextLetterX = letterDef.xAdvance + _additionalKerning;

    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
    for (int index = startIndex + 1; index < textLen; ++index)
    {
        character = utf32Text[index];
        if (!_fontAtlas->getLetterDefinitionForChar(character, letterDef))
        {
            break;
        }

        auto letterX = (nextLetterX + letterDef.offsetX) / contentScaleFactor;
        if (_maxLineWidth > 0.f && letterX + letterDef.width > _maxLineWidth
            && !StringUtils::isUnicodeSpace(character))
        {
            return len;
        }

        nextLetterX += letterDef.xAdvance + _additionalKerning;

        if (character == (char16_t)TextFormatter::NewLine
            || StringUtils::isUnicodeSpace(character)
            || StringUtils::isCJKUnicode(character))
        {
                break;
        }
        len++;
    }

    return len;
}

bool Label::multilineTextWrap(const std::function<int(const std::u32string&, int, int)>& nextTokenLen)
{
    int textLen = getStringLength();
    int lineIndex = 0;
    float nextTokenX = 0.f;
    float nextTokenY = 0.f;
    float longestLine = 0.f;
    float letterRight = 0.f;

    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
    float lineSpacing = _lineSpacing * contentScaleFactor;
    float highestY = 0.f;
    float lowestY = 0.f;
    FontLetterDefinition letterDef;
    Vec2 letterPosition;
    bool nextChangeSize = true;

    for (int index = 0; index < textLen; )
    {
        auto character = _utf32Text[index];
        if (character == (char32_t)TextFormatter::NewLine)
        {
            _linesWidth.push_back(letterRight);
            letterRight = 0.f;
            lineIndex++;
            nextTokenX = 0.f;
            nextTokenY -= _lineHeight + lineSpacing;
            recordPlaceholderInfo(index, character);
            index++;
            continue;
        }

        auto tokenLen = nextTokenLen(_utf32Text, index, textLen);
        float tokenHighestY = highestY;
        float tokenLowestY = lowestY;
        float tokenRight = letterRight;
        float nextLetterX = nextTokenX;
        bool newLine = false;
        for (int tmp = 0; tmp < tokenLen;++tmp)
        {
            int letterIndex = index + tmp;
            character = _utf32Text[letterIndex];
            if (character == (char16_t)TextFormatter::CarriageReturn)
            {
                recordPlaceholderInfo(letterIndex, character);
                continue;
            }
            // \b - Next char not change x position
            if (character == (char16_t)TextFormatter::NextCharNoChangeX)
            {
                nextChangeSize = false;
                recordPlaceholderInfo(letterIndex, character);
                continue;
            }
            if (!_fontAtlas->getLetterDefinitionForChar(character, letterDef))
            {
                recordPlaceholderInfo(letterIndex, character);
                CCLOG("LabelTextFormatter error:can't find letter definition in font file for letter: %c", character);
                continue;
            }

            auto letterX = (nextLetterX + letterDef.offsetX) / contentScaleFactor;
            if (_enableWrap && _maxLineWidth > 0.f && nextTokenX > 0.f && letterX + letterDef.width > _maxLineWidth
                && !StringUtils::isUnicodeSpace(character) && nextChangeSize)
            {
                _linesWidth.push_back(letterRight);
                letterRight = 0.f;
                lineIndex++;
                nextTokenX = 0.f;
                nextTokenY -= (_lineHeight + lineSpacing);
                newLine = true;
                break;
            }
            else
            {
                letterPosition.x = letterX;
            }
            letterPosition.y = (nextTokenY - letterDef.offsetY) / contentScaleFactor;
            recordLetterInfo(letterPosition, character, letterIndex, lineIndex);

            if (nextChangeSize)
            {
                if (_horizontalKernings && letterIndex < textLen - 1)
                    nextLetterX += _horizontalKernings[letterIndex + 1];
                nextLetterX += letterDef.xAdvance + _additionalKerning;

                    tokenRight = nextLetterX / contentScaleFactor;
                }
            nextChangeSize = true;

            if (tokenHighestY < letterPosition.y)
                tokenHighestY = letterPosition.y;
            if (tokenLowestY > letterPosition.y - letterDef.height)
                tokenLowestY = letterPosition.y - letterDef.height;
        }

        if (newLine)
        {
            continue;
        }

        nextTokenX = nextLetterX;
        letterRight = tokenRight;
        if (highestY < tokenHighestY)
            highestY = tokenHighestY;
        if (lowestY > tokenLowestY)
            lowestY = tokenLowestY;
        if (longestLine < letterRight)
            longestLine = letterRight;

        index += tokenLen;
    }

    _linesWidth.push_back(letterRight);

    _numberOfLines = lineIndex + 1;
    _textDesiredHeight = (_numberOfLines * _lineHeight) / contentScaleFactor;
    if (_numberOfLines > 1)
        _textDesiredHeight += (_numberOfLines - 1) * _lineSpacing;
    CSize contentSize(_labelWidth, _labelHeight);
    if (_labelWidth <= 0.f)
        contentSize.width = longestLine;
    if (_labelHeight <= 0.f)
        contentSize.height = _textDesiredHeight;
    setContentSize(contentSize);

    _tailoredTopY = contentSize.height;
    _tailoredBottomY = 0.f;
    if (highestY > 0.f)
        _tailoredTopY = contentSize.height + highestY;
    if (lowestY < -_textDesiredHeight)
        _tailoredBottomY = _textDesiredHeight + lowestY;

    return true;
}

bool Label::multilineTextWrapByWord()
{
    return multilineTextWrap(CC_CALLBACK_3(Label::getFirstWordLen, this));
}

bool Label::multilineTextWrapByChar()
{
    return multilineTextWrap(CC_CALLBACK_3(Label::getFirstCharLen, this));
}

bool Label::isVerticalClamp()
{
    if (_textDesiredHeight > _contentSize.height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Label::isHorizontalClamp()
{
    bool letterClamp = false;
    for (int ctr = 0; ctr < _lengthOfString; ++ctr)
    {
        if (_lettersInfo[ctr].valid)
        {
            auto& letterDef = _fontAtlas->_letterDefinitions[_lettersInfo[ctr].utf32Char];

            auto px = _lettersInfo[ctr].positionX + letterDef.width/2;
            auto lineIndex = _lettersInfo[ctr].lineIndex;

            if(_labelWidth > 0.f){
                if(!this->_enableWrap){
                    if (px > _contentSize.width) {
                        letterClamp = true;
                        break;
                    }
                }
                else{
                    auto wordWidth = this->_linesWidth[lineIndex];
                    if(wordWidth > this->_contentSize.width && (px > _contentSize.width)){
                        letterClamp = true;
                        break;
                    }

                }

            }
        }
    }

    return letterClamp;
}

void Label::shrinkLabelToContentSize(const std::function<bool(void)>& lambda)
{
    float fontSize = this->getRenderingFontSize();

    int i = 0;
    auto letterDefinition = _fontAtlas->_letterDefinitions;
    auto tempLetterDefinition = letterDefinition;
    float originalLineHeight = _lineHeight;
    bool flag = true;
    while (lambda()) {
        ++i;
        float newFontSize = fontSize - i;
        flag = false;
        if (newFontSize <= 0) {
            break;
        }
        float scale = newFontSize / fontSize;
        std::swap(_fontAtlas->_letterDefinitions, tempLetterDefinition);
        _fontAtlas->scaleFontLetterDefinition(scale);
        this->setLineHeight(originalLineHeight * scale);
        if (_maxLineWidth > 0.f && !_lineBreakWithoutSpaces)
        {
            multilineTextWrapByWord();
        }
        else
        {
            multilineTextWrapByChar();
        }
        computeAlignmentOffset();
        tempLetterDefinition = letterDefinition;
    }
    this->setLineHeight(originalLineHeight);
    std::swap(_fontAtlas->_letterDefinitions, letterDefinition);

    if (!flag) {
        if (fontSize - i >= 0) {
            this->scaleFontSizeDown(fontSize - i);
        }
    }
}

void Label::recordLetterInfo(const cocos2d::Vec2& point, char32_t utf32Char, int letterIndex, int lineIndex)
{
    if (static_cast<std::size_t>(letterIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }
    _lettersInfo[letterIndex].lineIndex = lineIndex;
    _lettersInfo[letterIndex].utf32Char = utf32Char;
    _lettersInfo[letterIndex].valid = _fontAtlas->_letterDefinitions[utf32Char].validDefinition;
    _lettersInfo[letterIndex].positionX = point.x;
    _lettersInfo[letterIndex].positionY = point.y;
    _lettersInfo[letterIndex].atlasIndex = -1;
}

void Label::recordPlaceholderInfo(int letterIndex, char32_t utf32Char)
{
    if (static_cast<std::size_t>(letterIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }
    _lettersInfo[letterIndex].utf32Char = utf32Char;
    _lettersInfo[letterIndex].valid = false;
}

NS_CC_END
