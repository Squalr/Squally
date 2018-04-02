#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Events/MouseEvents.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	static Mouse * claimInstance();
	static Mouse * getInstance();

	void setCanClick(bool canClick);

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

