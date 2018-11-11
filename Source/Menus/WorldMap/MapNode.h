#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Maps/Isometric/IsometricMap.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"

using namespace cocos2d;

class MapNode : public Node
{
public:
	static MapNode * create(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile);

	void setLocked(bool newLocked);
	bool isLocked();

	std::string nodeMapName;
	std::string nodeMapFile;

protected:
	MapNode(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile);
	~MapNode();

private:
	void initializePositions();
	void initializeListeners();
	void onNodeClick(MenuSprite* menuSprite);

	bool locked;
	MenuSprite* mapSprite;
	Sprite* mapSpriteLocked;
};

