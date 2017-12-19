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
	MapNode(std::string mapName, std::string mapFile, Vec2 position, bool tutorialNode, std::function<void(MapNode*)> onMouseOver);
	~MapNode();

	std::string nodeMapName;
	std::string nodeMapFile;

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	std::function<void(MapNode*)> onMouseOverEvent;

	Mouse* mouse;
	Sprite* sprite;
	Sprite* spriteLocked;
	Sprite* spriteSelected;
};

