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

#include "Engine/UI/Controls/UIWidget.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/renderer/CCGLProgram.h"
#include "cocos/renderer/CCGLProgramState.h"
#include "cocos/renderer/ccShaders.h"

using namespace cocos2d;

class Widget::FocusNavigationController
{
    void enableFocusNavigation(bool flag);

    FocusNavigationController():
        _firstFocusedWidget(nullptr),
        _enableFocusNavigation(false),
        _keyboardEventPriority(1)
    {
        //no-op
    }
    ~FocusNavigationController();

protected:
    void setFirstFocusedWidget(Widget* widget);

    void onKeypadKeyPressed(InputEvents::KeyCode keycode, EventCustom* eventCustom);

    friend class Widget;

private:
    Widget* _firstFocusedWidget ;
    bool _enableFocusNavigation ;
    const int _keyboardEventPriority;
};

Widget::FocusNavigationController::~FocusNavigationController()
{
}

void Widget::FocusNavigationController::onKeypadKeyPressed(InputEvents::KeyCode  keyCode, EventCustom* eventCustom)
{
    if (_enableFocusNavigation && _firstFocusedWidget)
    {
        if (keyCode == InputEvents::KeyCode::KEY_DPAD_DOWN)
        {
            _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::DOWN, _firstFocusedWidget);
        }
        if (keyCode == InputEvents::KeyCode::KEY_DPAD_UP)
        {
            _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::UP, _firstFocusedWidget);
        }
        if (keyCode == InputEvents::KeyCode::KEY_DPAD_LEFT)
        {
            _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::LEFT, _firstFocusedWidget);
        }
        if (keyCode == InputEvents::KeyCode::KEY_DPAD_RIGHT)
        {
            _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _firstFocusedWidget);
        }
    }
}

void Widget::FocusNavigationController::enableFocusNavigation(bool flag)
{
    if (_enableFocusNavigation == flag)
        return;

    _enableFocusNavigation = flag;
}

void Widget::FocusNavigationController::setFirstFocusedWidget(Widget* widget)
{
    _firstFocusedWidget = widget;
}

Widget* Widget::_focusedWidget = nullptr;
Widget::FocusNavigationController* Widget::_focusNavigationController = nullptr;

Widget::Widget():
_unifySize(false),
_enabled(true),
_bright(true),
_highlight(false),
_affectByClipping(false),
_ignoreSize(false),
_brightStyle(BrightStyle::NONE),
_sizeType(SizeType::ABSOLUTE),
_positionType(PositionType::ABSOLUTE),
_actionTag(0),
_customSize(CSize::ZERO),
_hitted(false),
_hittedByCamera(nullptr),
_flippedX(false),
_flippedY(false),
_focused(false),
_focusEnabled(true),
_ccEventCallback(nullptr),
_callbackType(""),
_callbackName(""),
keyEventListener(nullptr)
{

}

Widget::~Widget()
{
    this->cleanupWidget();
}

void Widget::cleanupWidget()
{
    // cleanup focused widget and focus navigation controller
    if (_focusedWidget == this)
    {
        // delete
        CC_SAFE_DELETE(_focusNavigationController);
        _focusedWidget = nullptr;
    }

    if (this->keyEventListener != nullptr)
    {
	    this->getEventDispatcher()->removeEventListener(this->keyEventListener);
    }
}

Widget* Widget::create()
{
    Widget* widget = new (std::nothrow) Widget();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Widget::init()
{
    if (Node::init())
    {
        initRenderer();
        setBright(true);
        onFocusChanged = CC_CALLBACK_2(Widget::onFocusChange,this);
        onNextFocusedWidget = nullptr;
        this->setAnchorPoint(Vec2(0.5f, 0.5f));

        this->keyEventListener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
        {
            if (this->_focusNavigationController && this->_focusNavigationController->_enableFocusNavigation)
            {
                InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getData());

                if (args != nullptr)
                {
                    this->_focusNavigationController->onKeypadKeyPressed(args->keycode, eventCustom);
                }
            }
        });
        
	    this->getEventDispatcher()->addEventListener(this->keyEventListener);

        ignoreContentAdaptWithSize(true);

        return true;
    }
    return false;
}

void Widget::onEnter()
{
    updateSizeAndPosition();
    Node::onEnter();
}

void Widget::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}

void Widget::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (_visible)
    {
        adaptRenderers();
        Node::visit(renderer, parentTransform, parentFlags);
    }
}

Widget* Widget::getWidgetParent()
{
    return dynamic_cast<Widget*>(getParent());
}

void Widget::setEnabled(bool enabled)
{
    _enabled = enabled;
    setBright(enabled);
}

void Widget::initRenderer()
{
}

void Widget::setContentSize(const cocos2d::CSize &contentSize)
{
    CSize previousSize = Node::getContentSize();
    if(previousSize.equals(contentSize))
    {
        return;
    }
    Node::setContentSize(contentSize);

    _customSize = contentSize;
    if (_unifySize)
    {
        //unify Size logic
    }
    else if (_ignoreSize)
    {
        Node::setContentSize(getVirtualRendererSize());
    }
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        CSize pSize;
        if (widgetParent)
        {
            pSize = widgetParent->getContentSize();
        }
        else
        {
            pSize = _parent->getContentSize();
        }
        float spx = 0.0f;
        float spy = 0.0f;
        if (pSize.width > 0.0f)
        {
            spx = _customSize.width / pSize.width;
        }
        if (pSize.height > 0.0f)
        {
            spy = _customSize.height / pSize.height;
        }
        _sizePercent.set(spx, spy);
    }
    onSizeChanged();
}

void Widget::setSizePercent(const Vec2 &percent)
{
    _sizePercent = percent;
    CSize cSize = _customSize;
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            cSize = CSize(widgetParent->getContentSize().width * percent.x, widgetParent->getContentSize().height * percent.y);
        }
        else
        {
            cSize = CSize(_parent->getContentSize().width * percent.x, _parent->getContentSize().height * percent.y);
        }
    }
    if (_ignoreSize)
    {
        this->setContentSize(getVirtualRendererSize());
    }
    else
    {
        this->setContentSize(cSize);
    }
    _customSize = cSize;
}

void Widget::updateSizeAndPosition()
{
    CSize pSize = _parent->getContentSize();

    updateSizeAndPosition(pSize);
}

void Widget::updateSizeAndPosition(const cocos2d::CSize &parentSize)
{
    switch (_sizeType)
    {
        case SizeType::ABSOLUTE:
        {
            if (_ignoreSize)
            {
                this->setContentSize(getVirtualRendererSize());
            }
            else
            {
                this->setContentSize(_customSize);
            }
            float spx = 0.0f;
            float spy = 0.0f;
            if (parentSize.width > 0.0f)
            {
                spx = _customSize.width / parentSize.width;
            }
            if (parentSize.height > 0.0f)
            {
                spy = _customSize.height / parentSize.height;
            }
            _sizePercent.set(spx, spy);
            break;
        }
        case SizeType::PERCENT:
        {
            CSize cSize = CSize(parentSize.width * _sizePercent.x , parentSize.height * _sizePercent.y);
            if (_ignoreSize)
            {
                this->setContentSize(getVirtualRendererSize());
            }
            else
            {
                this->setContentSize(cSize);
            }
            _customSize = cSize;
            break;
        }
        default:
            break;
    }

    //update position & position percent
    Vec2 absPos = getPosition();
    switch (_positionType)
    {
        case PositionType::ABSOLUTE:
        {
            if (parentSize.width <= 0.0f || parentSize.height <= 0.0f)
            {
                _positionPercent.setZero();
            }
            else
            {
                _positionPercent.set(absPos.x / parentSize.width, absPos.y / parentSize.height);
            }
            break;
        }
        case PositionType::PERCENT:
        {
            absPos.set(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            break;
        }
        default:
            break;
    }
    setPosition(absPos);
}

void Widget::setSizeType(SizeType type)
{
    _sizeType = type;
}
Widget::SizeType Widget::getSizeType() const
{
    return _sizeType;
}

void Widget::ignoreContentAdaptWithSize(bool ignore)
{
    if (_unifySize)
    {
        this->setContentSize(_customSize);
        return;
    }
    if (_ignoreSize == ignore)
    {
        return;
    }
    _ignoreSize = ignore;
    if (_ignoreSize)
    {
        CSize s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
}

bool Widget::isIgnoreContentAdaptWithSize() const
{
    return _ignoreSize;
}

const CSize& Widget::getCustomSize() const
{
    return _customSize;
}

const Vec2& Widget::getSizePercent()
{
    return _sizePercent;
}

Vec2 Widget::getWorldPosition()const
{
    return convertToWorldSpace(Vec2(_anchorPoint.x * _contentSize.width, _anchorPoint.y * _contentSize.height));
}

Node* Widget::getVirtualRenderer()
{
    return this;
}

void Widget::onSizeChanged()
{
    for (auto& child : getChildren())
    {
        Widget* widgetChild = dynamic_cast<Widget*>(child);
        if (widgetChild)
        {
            widgetChild->updateSizeAndPosition();
        }
    }
}

CSize Widget::getVirtualRendererSize() const
{
    return _contentSize;
}

void Widget::updateContentSizeWithTextureSize(const cocos2d::CSize &size)
{
    if (_unifySize)
    {
        this->setContentSize(size);
        return;
    }
    if (_ignoreSize)
    {
        this->setContentSize(size);
    }
    else
    {
        this->setContentSize(_customSize);
    }
}

bool Widget::isHighlighted() const
{
    return _highlight;
}

void Widget::setHighlighted(bool highlight)
{
    if (highlight == _highlight)
    {
        return;
    }

    _highlight = highlight;
    if (_bright)
    {
        if (_highlight)
        {
            setBrightStyle(BrightStyle::HIGHLIGHT);
        }
        else
        {
            setBrightStyle(BrightStyle::NORMAL);
        }
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBright(bool bright)
{
    _bright = bright;
    if (_bright)
    {
        _brightStyle = BrightStyle::NONE;
        setBrightStyle(BrightStyle::NORMAL);
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBrightStyle(BrightStyle style)
{
    if (_brightStyle == style)
    {
        return;
    }
    _brightStyle = style;
    switch (_brightStyle)
    {
        case BrightStyle::NORMAL:
            onPressStateChangedToNormal();
            break;
        case BrightStyle::HIGHLIGHT:
            onPressStateChangedToPressed();
            break;
        default:
            break;
    }
}

void Widget::onPressStateChangedToNormal()
{

}

void Widget::onPressStateChangedToPressed()
{

}

void Widget::onPressStateChangedToDisabled()
{

}

void Widget::updateChildrenDisplayedRGBA()
{
    this->setColor(this->getColor());
    this->setOpacity(this->getOpacity());
}


Widget* Widget::getAncestorWidget(Node* node)
{
    if (nullptr == node)
    {
        return nullptr;
    }

    Node* parent = node->getParent();
    if (nullptr == parent)
    {
        return nullptr;
    }
    Widget* parentWidget = dynamic_cast<Widget*>(parent);
    if (parentWidget)
    {
        return parentWidget;
    }
    else
    {
        return this->getAncestorWidget(parent->getParent());
    }
}

bool Widget::isAncestorsVisible(Node* node)
{
    if (nullptr == node)
    {
        return true;
    }
    Node* parent = node->getParent();

    if (parent && !parent->isVisible())
    {
        return false;
    }
    return this->isAncestorsVisible(parent);
}

bool Widget::isAncestorsEnabled()
{
    Widget* parentWidget = this->getAncestorWidget(this);
    if (parentWidget == nullptr)
    {
        return true;
    }
    if (parentWidget && !parentWidget->isEnabled())
    {
        return false;
    }

    return parentWidget->isAncestorsEnabled();
}

void Widget::pushDownEvent()
{
    this->retain();
    this->release();
}

void Widget::moveEvent()
{
    this->retain();
    this->release();
}

void Widget::releaseUpEvent()
{
    this->retain();

    if (isFocusEnabled())
    {
        requestFocus();
    }

    if (_clickEventListener) {
        _clickEventListener(this);
    }
    this->release();
}

void Widget::cancelUpEvent()
{
    this->retain();
    this->release();
}

void Widget::addClickEventListener(const ccWidgetClickCallback &callback)
{
    this->_clickEventListener = callback;
}

void Widget::addCCSEventListener(const ccWidgetEventCallback &callback)
{
    this->_ccEventCallback = callback;
}

bool Widget::hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const
{
    CRect rect;
    rect.size = getContentSize();
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}

bool Widget::isClippingParentContainsPoint(const Vec2 &pt)
{
    _affectByClipping = false;
    Node* parent = getParent();
    Widget* clippingParent = nullptr;
    while (parent)
    {
        parent = parent->getParent();
    }

    if (!_affectByClipping)
    {
        return true;
    }


    if (clippingParent)
    {
        bool bRet = false;
        auto camera = Camera::getVisitingCamera();
        // Camera isn't null means in touch begin process, otherwise use _hittedByCamera instead.
        if (clippingParent->hitTest(pt, (camera ? camera : _hittedByCamera), nullptr))
        {
            bRet = true;
        }
        if (bRet)
        {
            return clippingParent->isClippingParentContainsPoint(pt);
        }
        return false;
    }
    return true;
}

void Widget::setPosition(const Vec2 &pos)
{
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            CSize pSize = widgetParent->getContentSize();
            if (pSize.width <= 0.0f || pSize.height <= 0.0f)
            {
                _positionPercent.setZero();
            }
            else
            {
                _positionPercent.set(pos.x / pSize.width, pos.y / pSize.height);
            }
        }
    }
    Node::setPosition(pos);
}

void Widget::setPositionPercent(const Vec2 &percent)
{
    _positionPercent = percent;
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            CSize parentSize = widgetParent->getContentSize();
            Vec2 absPos(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            setPosition(absPos);
        }
    }
}

const Vec2& Widget::getPositionPercent()
{
    return _positionPercent;
}

void Widget::setPositionType(PositionType type)
{
    _positionType = type;
}

Widget::PositionType Widget::getPositionType() const
{
    return _positionType;
}

bool Widget::isBright() const
{
    return _bright;
}

bool Widget::isEnabled() const
{
    return _enabled;
}

float Widget::getLeftBoundary() const
{
    return getBoundingBox().origin.x;
}

float Widget::getBottomBoundary() const
{
    return getBoundingBox().origin.y;
}

float Widget::getRightBoundary() const
{
    return getLeftBoundary() + getBoundingBox().size.width;
}

float Widget::getTopBoundary() const
{
    return getBottomBoundary() + getBoundingBox().size.height;
}

std::string Widget::getDescription() const
{
    return "Widget";
}

Widget* Widget::clone()
{
    Widget* clonedWidget = createCloneInstance();
    clonedWidget->copyProperties(this);
    clonedWidget->copyClonedWidgetChildren(this);
    return clonedWidget;
}

Widget* Widget::createCloneInstance()
{
    return Widget::create();
}

void Widget::copyClonedWidgetChildren(Widget* model)
{
    auto& modelChildren = model->getChildren();

    for (auto& subWidget : modelChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            addChild(child->clone());
        }
    }
}

GLProgramState* Widget::getNormalGLProgramState(Texture2D* texture)const
{
    return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, texture);
}

GLProgramState* Widget::getGrayGLProgramState(Texture2D* texture)const
{
    return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE, texture);
}

void Widget::copySpecialProperties(Widget* /*model*/)
{

}

void Widget::copyProperties(Widget *widget)
{
    setEnabled(widget->isEnabled());
    setVisible(widget->isVisible());
    setBright(widget->isBright());
    setLocalZOrder(widget->getLocalZOrder());
    setName(widget->getName());
    setActionTag(widget->getActionTag());
    _ignoreSize = widget->_ignoreSize;
    this->setContentSize(widget->_contentSize);
    _customSize = widget->_customSize;
    _sizeType = widget->getSizeType();
    _sizePercent = widget->_sizePercent;
    _positionType = widget->_positionType;
    _positionPercent = widget->_positionPercent;
    setPosition(widget->getPosition());
    setAnchorPoint(widget->getAnchorPoint());
    setScaleX(widget->getScaleX());
    setScaleY(widget->getScaleY());
    setRotation(widget->getRotation());
    setFlippedX(widget->isFlippedX());
    setFlippedY(widget->isFlippedY());
    setColor(widget->getColor());
    setOpacity(widget->getOpacity());
    setCascadeColorEnabled(widget->isCascadeColorEnabled());
    setCascadeOpacityEnabled(widget->isCascadeOpacityEnabled());
    _clickEventListener = widget->_clickEventListener;
    _focused = widget->_focused;
    _focusEnabled = widget->_focusEnabled;

    copySpecialProperties(widget);
}

    void Widget::setFlippedX(bool flippedX)
    {

        float realScale = this->getScaleX();
        _flippedX = flippedX;
        this->setScaleX(realScale);
    }

    void Widget::setFlippedY(bool flippedY)
    {
        float realScale = this->getScaleY();
        _flippedY = flippedY;
        this->setScaleY(realScale);
    }



    void Widget::setScaleX(float scaleX)
    {
        if (_flippedX) {
            scaleX = scaleX * -1;
        }
        Node::setScaleX(scaleX);
    }

    void Widget::setScaleY(float scaleY)
    {
        if (_flippedY) {
            scaleY = scaleY * -1;
        }
        Node::setScaleY(scaleY);
    }

    void Widget::setScale(float scale)
    {
        this->setScaleX(scale);
        this->setScaleY(scale);
    }

    void Widget::setScale(float scaleX, float scaleY)
    {
        this->setScaleX(scaleX);
        this->setScaleY(scaleY);
    }

    float Widget::getScaleX()const
    {
        float originalScale = Node::getScaleX();
        if (_flippedX)
        {
            originalScale = originalScale * -1.0f;
        }
        return originalScale;
    }

    float Widget::getScaleY()const
    {
        float originalScale = Node::getScaleY();
        if (_flippedY)
        {
            originalScale = originalScale * -1.0f;
        }
        return originalScale;
    }

    float Widget::getScale()const
    {
        CCASSERT(this->getScaleX() == this->getScaleY(), "scaleX should be equal to scaleY.");
        return this->getScaleX();
    }


/*temp action*/
void Widget::setActionTag(int tag)
{
	_actionTag = tag;
}

int Widget::getActionTag()const
{
	return _actionTag;
}

void Widget::setFocused(bool focus)
{
    _focused = focus;

    //make sure there is only one focusedWidget
    if (focus) {
        _focusedWidget = this;
        if (_focusNavigationController) {
            _focusNavigationController->setFirstFocusedWidget(this);
        }
    }

}

bool Widget::isFocused()const
{
    return _focused;
}

void Widget::setFocusEnabled(bool enable)
{
    _focusEnabled = enable;
}

bool Widget::isFocusEnabled()const
{
    return _focusEnabled;
}

Widget* Widget::findNextFocusedWidget(FocusDirection direction,  Widget* current)
{
    if (nullptr == onNextFocusedWidget || nullptr == onNextFocusedWidget(direction) )
    {
        return current;
    }
    else
    {
        Widget *getFocusWidget = onNextFocusedWidget(direction);
        this->dispatchFocusEvent(this, getFocusWidget);
        return getFocusWidget;
    }
}

void Widget::dispatchFocusEvent(Widget *widgetLoseFocus, Widget *widgetGetFocus)
{
    //if the widgetLoseFocus doesn't get focus, it will use the previous focused widget instead
    if (widgetLoseFocus && !widgetLoseFocus->isFocused())
    {
        widgetLoseFocus = _focusedWidget;
    }

    if (widgetGetFocus != widgetLoseFocus)
    {

        if (widgetGetFocus)
        {
            widgetGetFocus->onFocusChanged(widgetLoseFocus, widgetGetFocus);
        }

        if (widgetLoseFocus)
        {
            widgetLoseFocus->onFocusChanged(widgetLoseFocus, widgetGetFocus);
        }

        // EventFocus event(widgetLoseFocus, widgetGetFocus);
        // auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
        // dispatcher->dispatchEvent(&event);
    }

}

void Widget::requestFocus()
{
    if (this == _focusedWidget)
    {
        return;
    }

    this->dispatchFocusEvent(_focusedWidget, this);
}

void Widget::onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus)
{
    //only change focus when there is indeed a get&lose happens
    if (widgetLostFocus)
    {
        widgetLostFocus->setFocused(false);
    }

    if (widgetGetFocus)
    {
        widgetGetFocus->setFocused(true);
    }
}

Widget* Widget::getCurrentFocusedWidget()
{
    return _focusedWidget;
}

void Widget::enableDpadNavigation(bool enable)
{
    if (enable)
    {
        if (nullptr == _focusNavigationController)
        {
            _focusNavigationController = new (std::nothrow) FocusNavigationController;
            if (_focusedWidget)
            {
                _focusNavigationController->setFirstFocusedWidget(_focusedWidget);
            }
        }
    }
    else
    {
        CC_SAFE_DELETE(_focusNavigationController);
    }

    if (nullptr != _focusNavigationController)
    {
        _focusNavigationController->enableFocusNavigation(enable);
    }
}


bool Widget::isUnifySizeEnabled()const
{
    return _unifySize;
}

void Widget::setUnifySizeEnabled(bool enable)
{
    _unifySize = enable;
}
