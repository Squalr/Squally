#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class CrystalPuzzle : public HackableObject
{
public:
	static CrystalPuzzle* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCrystalPuzzle;

protected:
	CrystalPuzzle(cocos2d::ValueMap& initProperties);
	virtual ~CrystalPuzzle();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void showActiveHackableCrystal();
	void incrementCrystalPuzzleAnimation();

	cocos2d::Sprite* gateLeft;
	cocos2d::Sprite* gateRight;
	cocos2d::Sprite* postLeft;
	cocos2d::Sprite* postRight;
	SmartAnimationSequenceNode* truthCrystal;
	cocos2d::Node* hackableCrystalNode;
	std::vector<cocos2d::Sprite*> hackableCrystalSprites;

	bool isUnlocked;
	int hackableIndex;
	int nextHackableIndex;
};
