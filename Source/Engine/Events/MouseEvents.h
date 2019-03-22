#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class MouseEvents
{
public:
	// Forward declarations
	struct MouseEventArgs;

	static void TriggerMouseMove(MouseEventArgs args);
	static void TriggerMouseRefresh(MouseEventArgs args);
	static void TriggerMouseDown(MouseEventArgs args);
	static void TriggerMouseUp(MouseEventArgs args);
	static void TriggerMouseScroll(MouseEventArgs args);
	static void TriggerStateChange(MouseEventArgs args);
	static void TriggerEventClickableMouseOver();
	static void TriggerClickableMouseOutEvent();
	static void TriggerDragEvent();

	struct MouseEventArgs
	{
		cocos2d::Vec2 mouseInitialCoords;
		cocos2d::Vec2 mouseCoords;
		cocos2d::Vec2 scrollDelta;
		bool isDragging;
		bool canClick;
		bool isLeftClicked;
		bool handled;

		MouseEventArgs(cocos2d::Vec2 mouseInitialCoords, cocos2d::Vec2 mouseCoords, cocos2d::Vec2 scrollDelta, bool isDragging, bool canClick, bool isLeftClicked) :
				mouseInitialCoords(mouseInitialCoords), mouseCoords(mouseCoords), scrollDelta(scrollDelta), isDragging(isDragging), canClick(canClick), isLeftClicked(isLeftClicked), handled(false)
		{
		}
	};

	static const std::string EventMouseMove;
	static const std::string EventMouseRefresh;
	static const std::string EventMouseDown;
	static const std::string EventMouseUp;
	static const std::string EventMouseScroll;
	static const std::string EventMouseStateUpdate;
	static const std::string EventClickableMouseOver;
	static const std::string ClickableMouseOutEvent;
	static const std::string EventMouseDrag;
};
