#pragma once

#include "Engine/SmartNode.h"
#include "Events/NavigationEvents.h"

class ClickableNode;

class LevelNode : public SmartNode
{
public:
	static LevelNode* create(std::string mapFile);

	void setLocked(bool newLocked);
	bool isLocked();

	std::string nodeMapFile;

protected:
	LevelNode(std::string mapFile);
	~LevelNode();

private:
	typedef SmartNode super;
	void initializePositions() override;
	void initializeListeners() override;
	void onNodeClick();

	bool locked;
	ClickableNode* mapSprite;
};
