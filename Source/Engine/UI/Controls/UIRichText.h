/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#pragma once

#include "Engine/UI/Controls/UIWidget.h"

#include "cocos/base/CCValue.h"

namespace cocos2d
{
    class Label;
}

class RichElement : public cocos2d::Ref
{
public:
    enum class Type
    {
        TEXT,   /*!< RichElementText */
        IMAGE,  /*!< RichElementImage */
        CUSTOM, /*!< RichElementCustomNode */
        NEWLINE /*!< RichElementNewLine */
    };
    
    RichElement() {};
    virtual ~RichElement() {};

    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity);
    
    bool equalType(Type type);
    void setColor(const cocos2d::Color3B& color);

protected:
    Type _type;             /*!< Rich element type. */
    int _tag;               /*!< A integer tag value. */
    cocos2d::Color3B _color;         /*!< A color in `cocos2d::Color3B`. */
    GLubyte _opacity;       /*!< A opacity value in `GLubyte`. */
    friend class RichText;
};

class RichElementText : public RichElement
{
public:
    RichElementText()
    {
        _type = Type::TEXT;
    };

    enum
    {
        ITALICS_FLAG = 1 << 0,          /*!< italic text */
        BOLD_FLAG = 1 << 1,             /*!< bold text */
        UNDERLINE_FLAG = 1 << 2,        /*!< underline */
        STRIKETHROUGH_FLAG = 1 << 3,    /*!< strikethrough */
        URL_FLAG = 1 << 4,              /*!< url of anchor */
        OUTLINE_FLAG = 1 << 5,          /*!< outline effect */
        SHADOW_FLAG = 1 << 6,           /*!< shadow effect */
        GLOW_FLAG = 1 << 7              /*!< glow effect */
    };
    
    virtual ~RichElementText(){};
    
    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& text,
              const std::string& fontName, float fontSize, uint32_t flags, const std::string& url,
              const cocos2d::Color3B& outlineColor = cocos2d::Color3B::WHITE, int outlineSize = -1,
              const cocos2d::Color3B& shadowColor = cocos2d::Color3B::BLACK, const cocos2d::CSize& shadowOffset = cocos2d::CSize(2.0, -2.0), int shadowBlurRadius = 0,
              const cocos2d::Color3B& glowColor = cocos2d::Color3B::WHITE);
    
    static RichElementText* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& text,
                                   const std::string& fontName, float fontSize, uint32_t flags=0, const std::string& url="",
                                   const cocos2d::Color3B& outlineColor = cocos2d::Color3B::WHITE, int outlineSize = -1,
                                   const cocos2d::Color3B& shadowColor = cocos2d::Color3B::BLACK, const cocos2d::CSize& shadowOffset = cocos2d::CSize(2.0, -2.0), int shadowBlurRadius = 0,
                                   const cocos2d::Color3B& glowColor = cocos2d::Color3B::WHITE);

                                   
    int getNewlineCount() { return _newlineCount; }
    
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    uint32_t _flags;
    std::string _url;
    cocos2d::Color3B _outlineColor;                  /*!< the color of the outline */
    int _outlineSize;                       /*!< the outline effect size value */
    cocos2d::Color3B _shadowColor;                   /*!< the shadow effect color value */
    cocos2d::CSize _shadowOffset;            /*!< shadow effect offset value */
    int _shadowBlurRadius;                  /*!< the shadow effect blur radius */
    cocos2d::Color3B _glowColor;                     /*!< attributes of glow tag */
    int _newlineCount;
    friend class RichText;
};

class RichElementImage : public RichElement
{
public:
    RichElementImage() { _type = Type::IMAGE; };
    virtual ~RichElementImage(){};

    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& filePath, const std::string& url = "", Widget::TextureResType texType = Widget::TextureResType::LOCAL);
    static RichElementImage* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& filePath, const std::string& url = "", Widget::TextureResType texType = Widget::TextureResType::LOCAL);

    void setWidth(int width);
    void setHeight(int height);
    void setUrl(const std::string& url);

protected:
    std::string _filePath;
    cocos2d::CRect _textureRect;
    Widget::TextureResType _textureType;
    friend class RichText;
    int _width;
    int _height;
    std::string _url;   /*!< attributes of anchor tag */
};

class RichElementCustomNode : public RichElement
{
public:
    RichElementCustomNode() { _type = Type::CUSTOM; };
    virtual ~RichElementCustomNode() { CC_SAFE_RELEASE(_customNode); };

    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, cocos2d::Node* customNode);
    static RichElementCustomNode* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, cocos2d::Node* customNode);

protected:
    cocos2d::Node* _customNode;
    friend class RichText;
};
    
class RichElementNewLine : public RichElement
{
public:
    RichElementNewLine(){_type = Type::NEWLINE;};
    virtual ~RichElementNewLine(){};

    static RichElementNewLine* create(int tag, const cocos2d::Color3B& color, GLubyte opacity);
protected:
    friend class RichText;
};

class RichText : public Widget
{
public:

    enum WrapMode {
        WRAP_PER_WORD,
        WRAP_PER_CHAR
    };
    
    enum class HorizontalAlignment {
        LEFT,
        CENTER,
        RIGHT,
    };

    typedef std::function<void(const std::string& url)> OpenUrlHandler;
    typedef std::function<std::pair<cocos2d::ValueMap, RichElement*>(const cocos2d::ValueMap& tagAttrValueMap)> VisitEnterHandler;
    
    static const std::string KEY_VERTICAL_SPACE;                    /*!< key of vertical space */
    static const std::string KEY_WRAP_MODE;                         /*!< key of per word, or per char */
    static const std::string KEY_HORIZONTAL_ALIGNMENT;              /*!< key of left, right, or center */
    static const std::string KEY_FONT_COLOR_STRING;                 /*!< key of font color */
    static const std::string KEY_FONT_SIZE;                         /*!< key of font size */
    static const std::string KEY_FONT_SMALL;                        /*!< key of font size small */
    static const std::string KEY_FONT_BIG;                          /*!< key of font size big */
    static const std::string KEY_FONT_FACE;                         /*!< key of font name */
    static const std::string KEY_TEXT_BOLD;                         /*!< key of text bold */
    static const std::string KEY_TEXT_ITALIC;                       /*!< key of text italic */
    static const std::string KEY_TEXT_LINE;                         /*!< key of line style */
    static const std::string VALUE_TEXT_LINE_NONE;                  /*!< value of none */
    static const std::string VALUE_TEXT_LINE_DEL;                   /*!< value of strikethrough line */
    static const std::string VALUE_TEXT_LINE_UNDER;                 /*!< value of underline */
    static const std::string KEY_TEXT_STYLE;                        /*!< key of effect style */
    static const std::string VALUE_TEXT_STYLE_NONE;                 /*!< value of none */
    static const std::string VALUE_TEXT_STYLE_OUTLINE;              /*!< value of outline */
    static const std::string VALUE_TEXT_STYLE_SHADOW;               /*!< value of shadow */
    static const std::string VALUE_TEXT_STYLE_GLOW;                 /*!< value of glow */
    static const std::string KEY_TEXT_OUTLINE_COLOR;                /*!< key of outline color */
    static const std::string KEY_TEXT_OUTLINE_SIZE;                 /*!< key of outline size */
    static const std::string KEY_TEXT_SHADOW_COLOR;                 /*!< key of shadow color */
    static const std::string KEY_TEXT_SHADOW_OFFSET_WIDTH;          /*!< key of shadow offset (width) */
    static const std::string KEY_TEXT_SHADOW_OFFSET_HEIGHT;         /*!< key of shadow offset (height) */
    static const std::string KEY_TEXT_SHADOW_BLUR_RADIUS;           /*!< key of shadow blur radius */
    static const std::string KEY_TEXT_GLOW_COLOR;                   /*!< key of glow color */
    static const std::string KEY_URL;                               /*!< key of url */
    static const std::string KEY_ANCHOR_FONT_COLOR_STRING;          /*!< key of font color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_BOLD;                  /*!< key of text bold of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_ITALIC;                /*!< key of text italic of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_LINE;                  /*!< key of line style of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_STYLE;                 /*!< key of effect style of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_OUTLINE_COLOR;         /*!< key of outline color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_OUTLINE_SIZE;          /*!< key of outline size of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_COLOR;          /*!< key of shadow color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH;   /*!< key of shadow offset (width) of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT;  /*!< key of shadow offset (height) of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS;    /*!< key of shadow blur radius of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_GLOW_COLOR;            /*!< key of glow color of anchor tag */
    
    RichText();
    virtual ~RichText();

    static RichText* create();
    void insertElement(RichElement* element, int index);
    void pushBackElement(RichElement* element);
    void removeElement(int index);
	void removeElement(RichElement* element);
	void clearElements();
    void setVerticalSpace(float space);
    void formatText();

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;

    void setWrapMode(WrapMode wrapMode);                /*!< sets the wrapping mode: WRAP_PER_CHAR or WRAP_PER_WORD */
    WrapMode getWrapMode() const;                       /*!< returns the current wrapping mode */
    void setHorizontalAlignment(HorizontalAlignment a); /*!< sets the horizontal alignment mode: LEFT, CENTER, or RIGHT */
    HorizontalAlignment getHorizontalAlignment() const; /*!< returns the current horizontal alignment mode */
    void setFontColor(const std::string& color);        /*!< Set the font color. @param color the #RRGGBB hexadecimal notation. */
    std::string getFontColor();                         /*!< return the current font color */
    cocos2d::Color3B getFontColor3B();                           /*!< return the current font color */
    void setFontSize(float size);                       /*!< Set the font size. @param size the font size. */
    float getFontSize();                                /*!< return the current font size */
    void setFontFace(const std::string& face);          /*!< Set the font face. @param face the font face. */
    std::string getFontFace();                          /*!< return the current font face */
    void setAnchorFontColor(const std::string& color);  /*!< Set the font color of a-tag. @param face the font color. */
    std::string getAnchorFontColor();                   /*!< return the current font color of a-tag */
    cocos2d::Color3B getAnchorFontColor3B();            /*!< return the current font color of a-tag */
    void setAnchorTextBold(bool enable);                /*!< enable bold text of a-tag */
    bool isAnchorTextBoldEnabled();                     /*!< valid style is bold text of a-tag? */
    void setAnchorTextItalic(bool enable);              /*!< enable italic text of a-tag */
    bool isAnchorTextItalicEnabled();                   /*!< valid style is italic text of a-tag? */
    void setAnchorTextDel(bool enable);                 /*!< enable the strikethrough of a-tag */
    bool isAnchorTextDelEnabled();                      /*!< valid strikethrough of a-tag? */
    void setAnchorTextUnderline(bool enable);           /*!< enable the underline of a-tag */
    bool isAnchorTextUnderlineEnabled();                /*!< valid underline of a-tag? */
    /** @brief enable the outline of a-tag */
    void setAnchorTextOutline(bool enable, const cocos2d::Color3B& outlineColor = cocos2d::Color3B::WHITE, int outlineSize = -1);
    bool isAnchorTextOutlineEnabled();                  /*!< valid outline of a-tag? */
    cocos2d::Color3B getAnchorTextOutlineColor3B();              /*!< return the current text outline color of a-tag */
    int getAnchorTextOutlineSize();                     /*!< return the current text outline size of a-tag */
    /** @brief enable the shadow of a-tag */
    void setAnchorTextShadow(bool enable, const cocos2d::Color3B& shadowColor = cocos2d::Color3B::BLACK, const cocos2d::CSize& offset = cocos2d::CSize(2.0, -2.0), int blurRadius = 0);
    bool isAnchorTextShadowEnabled();                   /*!< valid shadow of a-tag? */
    cocos2d::Color3B getAnchorTextShadowColor3B();               /*!< return the current text shadow color of a-tag */
    cocos2d::CSize getAnchorTextShadowOffset();                  /*!< return the current text shadow offset of a-tag */
    int getAnchorTextShadowBlurRadius();                /*!< return the current text shadow blur radius of a-tag */
    void setAnchorTextGlow(bool enable, const cocos2d::Color3B& glowColor = cocos2d::Color3B::WHITE); /*!< enable the glow of a-tag */
    bool isAnchorTextGlowEnabled();                     /*!< valid glow of a-tag? */
    cocos2d::Color3B getAnchorTextGlowColor3B();                 /*!< return the current text glow color of a-tag */
    void setDefaults(const cocos2d::ValueMap& defaults);         /*!< set the default values */
    cocos2d::ValueMap getDefaults() const;                       /*!< returns the default values */

    cocos2d::Color3B color3BWithString(const std::string& color);   /*!< convert a color string into a color3B. */
    std::string stringWithColor3B(const cocos2d::Color3B& color3B); /*!< convert a color3B into a color string. */
    std::string stringWithColor4B(const cocos2d::Color4B& color4b); /*!< convert a Color4B into a color string. */

    static void setTagDescription(const std::string& tag, bool isFontElement, VisitEnterHandler handleVisitEnter);
    static void removeTagDescription(const std::string& tag);
    
    void openUrl(const std::string& url);
    void setOpenUrlHandler(const OpenUrlHandler& handleOpenUrl);

    int getNewlineCount();

    virtual bool init() override;
    
protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(RichElementText* elmtText, const std::string& text, const std::string& fontName, float fontSize, const cocos2d::Color3B& color,
                            GLubyte opacity, uint32_t flags, const std::string& url = "",
                            const cocos2d::Color3B& outlineColor = cocos2d::Color3B::WHITE, int outlineSize = -1,
                            const cocos2d::Color3B& shadowColor = cocos2d::Color3B::BLACK, const cocos2d::CSize& shadowOffset = cocos2d::CSize(2.0, -2.0), int shadowBlurRadius = 0,
                            const cocos2d::Color3B& glowColor = cocos2d::Color3B::WHITE);
    void handleImageRenderer(const std::string& filePath, const cocos2d::Color3B& color, GLubyte opacity, int width, int height, const std::string& url);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
    int findSplitPositionForWord(cocos2d::Label* label, const std::string& text);
    int findSplitPositionForChar(cocos2d::Label* label, const std::string& text);
	void doHorizontalAlignment(const cocos2d::Vector<Node*>& row, float rowWidth);
	float stripTrailingWhitespace(const cocos2d::Vector<Node*>& row);

    bool _formatTextDirty;
    cocos2d::Vector<RichElement*> _richElements;
    std::vector<cocos2d::Vector<Node*>> _elementRenders;
    float _leftSpaceWidth;

    cocos2d::ValueMap _defaults;             /*!< default values */
    OpenUrlHandler _handleOpenUrl;  /*!< the callback for open URL */
};
