#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MouseEvents
{
public:
	static const std::string MouseMoveEvent;
	static const std::string MouseCanClickEvent;

	struct MouseEventArgs
	{
		float mouseX;
		float mouseY;
		EventMouse* innerEvent;
		bool handled;

		MouseEventArgs(float x, float y, EventMouse* event) : mouseX(x), mouseY(y), innerEvent(event), handled(false)
		{
		}
	};

	struct MouseCanClickEventArgs
	{
		bool canClick;

		MouseCanClickEventArgs(bool canClick) : canClick(canClick)
		{
		}
	};

	static void TriggerCanClickEvent(MouseCanClickEventArgs args);
	static void TriggerMouseMove(MouseEventArgs args);
};
