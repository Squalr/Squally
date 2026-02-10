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

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCInputEvents.h"

NS_CC_BEGIN

const std::string InputEvents::EventMouseMoveInternal = "EVENT_MOUSE_MOVE_INTERNAL";
const std::string InputEvents::EventMouseDownInternal = "EVENT_MOUSE_DOWN_INTERNAL";
const std::string InputEvents::EventMouseUpInternal = "EVENT_MOUSE_UP_INTERNAL";
const std::string InputEvents::EventMouseScrollInternal = "EVENT_MOUSE_SCROLL_INTERNAL";
const std::string InputEvents::EventKeyJustPressedInternal = "EVENT_KEY_JUST_PRESSED_INTERNAL";
const std::string InputEvents::EventKeyJustReleasedInternal = "EVENT_KEY_JUST_RELEASED_INTERNAL";

const std::string InputEvents::EventMouseHitTest = "EVENT_MOUSE_HIT_TEST";
const std::string InputEvents::EventMouseMove = "EVENT_MOUSE_MOVE";
const std::string InputEvents::EventMouseRequestRefresh = "EVENT_MOUSE_REQUEST_REFRESH";
const std::string InputEvents::EventMouseRefresh = "EVENT_MOUSE_REFRESH";
const std::string InputEvents::EventMouseDown = "EVENT_MOUSE_DOWN";
const std::string InputEvents::EventMouseUp = "EVENT_MOUSE_UP";
const std::string InputEvents::EventMouseScroll = "EVENT_MOUSE_SCROLL";
const std::string InputEvents::EventClickableMouseOver = "EVENT_CLICKABLE_MOUSE_OVER";
const std::string InputEvents::EventClickableMouseOut = "EVENT_CLICKABLE_MOUSE_OUT";
const std::string InputEvents::EventMouseDrag = "EVENT_MOUSE_DRAG";
const std::string InputEvents::EventMouseStateUpdate = "EVENT_MOUSE_STATE_UPDATE";
const std::string InputEvents::EventKeyJustPressed = "EVENT_KEY_JUST_PRESSED";
const std::string InputEvents::EventKeyJustReleased = "EVENT_KEY_JUST_RELEASED";

void InputEvents::TriggerMouseMoveInternal(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseMoveInternal,
		&args
	);
}

void InputEvents::TriggerMouseDownInternal(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseDownInternal,
		&args
	);
}

void InputEvents::TriggerMouseUpInternal(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseUpInternal,
		&args
	);
}

void InputEvents::TriggerMouseScrollInternal(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseScrollInternal,
		&args
	);
}

void InputEvents::TriggerKeyJustPressedInternal(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventKeyJustPressedInternal,
		&args
	);
}

void InputEvents::TriggerKeyJustReleasedInternal(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventKeyJustReleasedInternal,
		&args
	);
}

void InputEvents::TriggerMouseHitTest(MouseHitTestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseHitTest,
		&args
	);
}

void InputEvents::TriggerMouseMove(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseMove,
		&args
	);
}

void InputEvents::TriggerMouseRequestRefresh()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseRequestRefresh
	);
}

void InputEvents::TriggerMouseRefresh(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseRefresh,
		&args
	);
}

void InputEvents::TriggerMouseDown(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseDown,
		&args
	);
}

void InputEvents::TriggerMouseUp(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseUp,
		&args
	);
}

void InputEvents::TriggerMouseScroll(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseScroll,
		&args
	);
}

void InputEvents::TriggerStateChange(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseStateUpdate,
		&args
	);
}

void InputEvents::TriggerEventClickableMouseOver()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventClickableMouseOver
	);
}

void InputEvents::TriggerEventClickableMouseOut()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventClickableMouseOut
	);
}

void InputEvents::TriggerDragEvent()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventMouseDrag
	);
}

void InputEvents::TriggerKeyJustPressed(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventKeyJustPressed,
		&args
	);
}

void InputEvents::TriggerKeyJustReleased(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		InputEvents::EventKeyJustReleased,
		&args
	);
}

NS_CC_END
