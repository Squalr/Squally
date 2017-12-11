#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public Node
{
public:
	Mouse();
	~Mouse();

	void SetCanClick(bool canClick);

	void onEnter() override;

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;
};

