#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	static Mouse * claimInstance();
	static Mouse * getInstance();

	void SetCanClick(bool canClick);

	const std::string MouseMoveEvent = "mouse_move_event";

	struct MouseEventArgs
	{
		float mouseX;
		float mouseY;
		MouseEventArgs(float x, float y) : mouseX(x), mouseY(y)
		{
		}
	};

protected:
	Mouse();
	~Mouse();

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;

	static Mouse * mouseInstance;
};

