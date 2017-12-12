#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Mouse.h"
#include "Level/Level.h"

using namespace cocos2d;

class MapNode : public Node
{
public:
	MapNode(Vec2 position, bool tutorialNode);
	~MapNode();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMouseDown(EventMouse* event);

	Mouse* mouse;
	Sprite* sprite;
};

