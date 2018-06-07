#pragma once
#include "cocos2d.h"

#include "Events/MouseEvents.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	static Mouse * create();

protected:
	Mouse();
	~Mouse();

private:
	void initializeListeners();
	void onMouseCanClickEvent(EventCustom* eventCustom);
	void setCanClick(bool canClick);
	void onMouseMove(EventMouse* event);
	void onEnter() override;

	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;

	static Vec2 mousePosition;
};

