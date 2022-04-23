/****************************************************************************
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

#pragma once

#include "cocos/2d/CCNode.h"

namespace cocos2d
{
    class Camera;
    class EventCustom;
    class EventListenerCustom;
}

/**
 *@brief Base class for all ui widgets.
 */
class Widget : public cocos2d::Node
{
public:
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };

    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };

    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    typedef std::function<void(cocos2d::Ref*)> ccWidgetClickCallback;
    typedef std::function<void(cocos2d::Ref*, int)> ccWidgetEventCallback;

    Widget(void);
    virtual ~Widget();

    static Widget* create();

    virtual void setEnabled(bool enabled);
    bool isEnabled() const;
    void setBright(bool bright);
    bool isBright() const;
    void setBrightStyle(BrightStyle style);
    bool isHighlighted() const;
    void setHighlighted(bool highlight);
    float getLeftBoundary() const;
    float getBottomBoundary() const;
    float getRightBoundary() const;
    float getTopBoundary() const;
    virtual void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
    void addClickEventListener(const ccWidgetClickCallback& callback);
    virtual void addCCSEventListener(const ccWidgetEventCallback& callback);
    virtual void setPosition(const cocos2d::Vec2& pos) override;
    void setPositionPercent(const cocos2d::Vec2& percent);
    const cocos2d::Vec2& getPositionPercent();

    void setPositionType(PositionType type);
    PositionType getPositionType() const;
    void setFlippedX(bool flippedX);
    virtual bool isFlippedX() const {return _flippedX;};
    virtual void setFlippedY(bool flippedY);
    virtual bool isFlippedY() const {return _flippedY;};

    //override the setScale function of Node
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scale) override;
    virtual void setScale(float scalex, float scaley) override;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;
    virtual float getScale() const override;

    bool isClippingParentContainsPoint(const cocos2d::Vec2& pt);
    virtual void setContentSize(const cocos2d::CSize& contentSize) override;
    virtual void setSizePercent(const cocos2d::Vec2 &percent);
    void setSizeType(SizeType type);
    SizeType getSizeType() const;
    const cocos2d::CSize& getCustomSize() const;
    virtual const cocos2d::CSize& getLayoutSize() {return _contentSize;};
    const cocos2d::Vec2& getSizePercent();
    virtual bool hitTest(const cocos2d::Vec2 &pt, const Camera* camera, cocos2d::Vec3 *p) const;
    virtual void ignoreContentAdaptWithSize(bool ignore);
    bool isIgnoreContentAdaptWithSize() const;
    cocos2d::Vec2 getWorldPosition()const;
    virtual Node* getVirtualRenderer();
    virtual cocos2d::CSize getVirtualRendererSize() const;
    virtual std::string getDescription() const override;

    Widget* clone();
    virtual void onEnter() override;
    virtual void onExit() override;
    void updateSizeAndPosition();
    void updateSizeAndPosition(const cocos2d::CSize& parentSize);
    void setActionTag(int tag);
    int getActionTag()const;
    bool isFocused()const;
    void setFocused(bool focus);
    bool isFocusEnabled()const;
    void setFocusEnabled(bool enable);
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    void requestFocus();
    static Widget* getCurrentFocusedWidget();
    static void enableDpadNavigation(bool enable);

    std::function<void(Widget*,Widget*)> onFocusChanged;
    std::function<Widget*(FocusDirection)> onNextFocusedWidget;

    void setUnifySizeEnabled(bool enable);
    bool isUnifySizeEnabled()const;
    void setCallbackName(const std::string& callbackName) { _callbackName = callbackName; }
    const std::string& getCallbackName() const{ return _callbackName; }
    void setCallbackType(const std::string& callbackType) { _callbackType = callbackType; }
    const std::string& getCallbackType() const{ return _callbackType; }

    virtual bool init() override;
    
    friend class PageView;

    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    void  dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);
    
protected:
    cocos2d::GLProgramState* getNormalGLProgramState(cocos2d::Texture2D* texture)const;
    cocos2d::GLProgramState* getGrayGLProgramState(cocos2d::Texture2D* texture)const;
     
    virtual void onSizeChanged();
    virtual void initRenderer();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();

    void pushDownEvent();
    void moveEvent();

    virtual void releaseUpEvent();
    virtual void cancelUpEvent();

    
    virtual void adaptRenderers(){};
    void updateChildrenDisplayedRGBA();
    
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const cocos2d::CSize& size);
    
    bool isAncestorsEnabled();
    Widget* getAncestorWidget(Node* node);
    bool isAncestorsVisible(Node* node);

    void cleanupWidget();

protected:
    bool _unifySize;
    bool _enabled;
    bool _bright;
    bool _highlight;
    bool _affectByClipping;
    bool _ignoreSize;

    BrightStyle _brightStyle;
    SizeType _sizeType;
    PositionType _positionType;

    //used for search widget by action tag in UIHelper class
    int _actionTag;

    cocos2d::CSize _customSize;

    cocos2d::Vec2 _sizePercent;
    cocos2d::Vec2 _positionPercent;

    bool _hitted;

    // weak reference of the camera which made the widget passed the hit test when response touch begin event
    // it's useful in the next touch move/end events
    const cocos2d::Camera* _hittedByCamera;

    bool _flippedX;
    bool _flippedY;

    bool _focused;
    bool _focusEnabled;
    static Widget* _focusedWidget;  //both layout & widget will be stored in this variable

    ccWidgetClickCallback _clickEventListener;
    ccWidgetEventCallback _ccEventCallback;
    
    std::string _callbackType;
    std::string _callbackName;
private:
    class FocusNavigationController;
    static FocusNavigationController* _focusNavigationController;

    cocos2d::EventListenerCustom* keyEventListener;
};
