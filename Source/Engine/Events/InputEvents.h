#pragma once
#include <string>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/math/Vec2.h"

class InputEvents
{
public:
	static const std::string EventMouseMove;
	static const std::string EventMouseRefresh;
	static const std::string EventMouseDown;
	static const std::string EventMouseUp;
	static const std::string EventMouseScroll;
	static const std::string EventMouseStateUpdate;
	static const std::string EventClickableMouseOver;
	static const std::string EventClickableMouseOut;
	static const std::string EventMouseDrag;
	static const std::string EventKeyJustPressed;
	static const std::string EventKeyJustReleased;

	struct MouseEventArgs
	{
		cocos2d::Vec2 mouseInitialCoords;
		cocos2d::Vec2 mouseCoords;
		cocos2d::Vec2 scrollDelta;
		bool isDragging;
		bool canClick;
		bool isLeftClicked;

		MouseEventArgs(cocos2d::Vec2 mouseInitialCoords, cocos2d::Vec2 mouseCoords, cocos2d::Vec2 scrollDelta, bool isDragging, bool canClick, bool isLeftClicked) :
				mouseInitialCoords(mouseInitialCoords), mouseCoords(mouseCoords), scrollDelta(scrollDelta), isDragging(isDragging), canClick(canClick), isLeftClicked(isLeftClicked), handled(false)
		{
		}

		void handle()
		{
			this->handled = true;
		}

		void unhandle()
		{
			this->handled = false;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
	};

	struct InputArgs
	{
		cocos2d::EventKeyboard::KeyCode keycode;

		InputArgs(cocos2d::EventKeyboard::KeyCode keycode) : keycode(keycode), handled(false) { }

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
	};

	static void TriggerMouseMove(MouseEventArgs args);
	static void TriggerMouseRefresh(MouseEventArgs args);
	static void TriggerMouseDown(MouseEventArgs args);
	static void TriggerMouseUp(MouseEventArgs args);
	static void TriggerMouseScroll(MouseEventArgs args);
	static void TriggerStateChange(MouseEventArgs args);
	static void TriggerEventClickableMouseOver();
	static void TriggerEventClickableMouseOut();
	static void TriggerDragEvent();
	static void TriggerKeyJustPressed(InputArgs args);
	static void TriggerKeyJustReleased(InputArgs args);
};
