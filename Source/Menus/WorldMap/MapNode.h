#pragma once

#include "Engine/SmartNode.h"
#include "Events/NavigationEvents.h"

class MenuSprite;

class MapNode : public SmartNode
{
public:
	static MapNode* create(std::string mapFile);

	void setLocked(bool newLocked);
	bool isLocked();

	std::string nodeMapFile;

protected:
	MapNode(std::string mapFile);
	~MapNode();

private:
	void initializePositions() override;
	void initializeListeners() override;
	void onNodeClick(MenuSprite* menuSprite);

	bool locked;
	MenuSprite* mapSprite;
};

