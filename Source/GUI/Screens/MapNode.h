#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Mouse.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MapNode : public Node
{
public:
	MapNode(Vec2 position, bool tutorialNode);
	~MapNode();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	Mouse* mouse;
	Sprite* sprite;
	Sprite* spriteLocked;
	Sprite* spriteSelected;
};

