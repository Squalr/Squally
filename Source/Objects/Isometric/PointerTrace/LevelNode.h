#pragma once

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;

class LevelNode : public HackableObject
{
public:
	static LevelNode* create(const cocos2d::ValueMap& properties);

	void setLocked(bool newLocked);
	bool isLocked();
	cocos2d::Vec2 getPositionOffset();

	std::string nodeMapFile;

	static const std::string MapKeyLevelNode;

protected:
	LevelNode(const cocos2d::ValueMap& properties);
	~LevelNode();

private:
	typedef HackableObject super;
	void initializePositions() override;
	void initializeListeners() override;

	bool locked;
	ClickableNode* mapSprite;

	static const std::string MapKeyMapFile;
	static const std::string MapKeyIndex;
};
