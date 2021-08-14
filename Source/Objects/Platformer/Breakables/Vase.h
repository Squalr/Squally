#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class SmartParticles;
class WorldSound;

class Vase : public BreakableBase
{
public:
	static Vase* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Vase(cocos2d::ValueMap& properties, int requiredHits = 1);
	virtual ~Vase();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;

private:
	typedef BreakableBase super;

	WorldSound* breakSound = nullptr;
	SmartAnimationSequenceNode* explosion = nullptr;
	cocos2d::Sprite* vase = nullptr;
	CollisionObject* vaseBroken = nullptr;
	SmartParticles* shardParticles = nullptr;
	std::string color;
};
