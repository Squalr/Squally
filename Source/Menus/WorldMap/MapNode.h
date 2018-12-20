#pragma once

#include "Engine/SmartNode.h"
#include "Events/NavigationEvents.h"

class MenuSprite;

class MapNode : public SmartNode
{
public:
	static MapNode* create(std::string mapName, std::string mapFile);

	void setLocked(bool newLocked);
	bool isLocked();

	std::string nodeMapName;
	std::string nodeMapFile;

protected:
	MapNode(std::string mapName, std::string mapFile);
	~MapNode();

private:
	void initializePositions();
	void initializeListeners();
	void onNodeClick(MenuSprite* menuSprite);

	bool locked;
	MenuSprite* mapSprite;
};

