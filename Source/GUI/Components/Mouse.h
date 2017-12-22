#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	static Mouse * create();

	void SetCanClick(bool canClick);

protected:
	Mouse();
	~Mouse();

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;
};

