#pragma once

#include "Engine/SmartNode.h"

class ClickableNode;

class LevelNode : public SmartNode
{
public:
	static LevelNode* deserialize(std::string mapFile, cocos2d::Vec2 positionOffset = cocos2d::Vec2::ZERO);

	void setLocked(bool newLocked);
	bool isLocked();
	cocos2d::Vec2 getPositionOffset();

	std::string nodeMapFile;

protected:
	LevelNode(std::string mapFile, cocos2d::Vec2 positionOffset);
	~LevelNode();

private:
	typedef SmartNode super;
	void initializePositions() override;
	void initializeListeners() override;
	void onNodeClick();

	bool locked;
	cocos2d::Vec2 positionOffset;
	ClickableNode* mapSprite;
};
