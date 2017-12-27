#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	static Mouse * claimInstance();
	static Mouse * getInstance();

	void setCanClick(bool canClick);

	const std::string MouseMoveEvent = "mouse_move_event";

	struct MouseEventArgs
	{
		float mouseX;
		float mouseY;
		EventMouse* innerEvent;

		MouseEventArgs(float x, float y, EventMouse* event) : mouseX(x), mouseY(y), innerEvent(event)
		{
		}
	};

protected:
	Mouse();
	~Mouse();

private:
	void initializeListeners();
	void onMouseMove(EventMouse* event);

	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;

	static Mouse * mouseInstance;
};

