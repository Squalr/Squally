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

	static const std::string MouseMoveEvent;

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

