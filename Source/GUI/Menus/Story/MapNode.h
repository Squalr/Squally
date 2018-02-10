#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuSprite.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MapNode : public Node
{
public:
	static MapNode * create(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile);

	void setLocked(bool isLocked);
	void setCallBack(std::function<void(MapNode*)> onMouseOver);

	std::string nodeMapName;
	std::string nodeMapFile;

protected:
	MapNode(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile);
	~MapNode();

private:
	void initializePositions();
	void initializeListeners();
	void onNodeClick(MenuSprite* menuSprite, EventMouse* args);

	std::function<void(MapNode*)> onMouseOverEvent;

	Mouse* mouse;
	MenuSprite* mapSprite;
	Sprite* mapSpriteLocked;
};

