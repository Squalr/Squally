#pragma once

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;

namespace cocos2d
{
	class Sprite;
}

class LevelNode : public HackableObject
{
public:
	static LevelNode* create(const cocos2d::ValueMap& properties);

	cocos2d::Vec2 getPositionOffset();

	std::string nodeMapFile;

	static const std::string MapKeyLevelNode;

protected:
	LevelNode(const cocos2d::ValueMap& properties);
	~LevelNode();

private:
	typedef HackableObject super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void setLockState();
	std::string getSaveKey();
	std::string getPreviousSaveKey();

	int levelIndex;
	int groupIndex;
	bool isGroupFinale;
	cocos2d::Sprite* disabledSprite;
	ClickableNode* sprite;

	static const std::string MapKeyMapFile;
	static const std::string MapKeyGroupIndex;
	static const std::string MapKeyGroupFinale;
	static const std::string MapKeyLevelIndex;
	static const std::string SaveKeyPrefix;
};
