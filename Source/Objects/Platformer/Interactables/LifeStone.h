#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class PhysicsBody;
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class LifeStone : public HackableObject
{
public:
	static LifeStone* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyLifeStone;

protected:
	LifeStone(cocos2d::ValueMap& properties);
	~LifeStone();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	void runHealAnimation(bool reRun = false);

	cocos2d::Sprite* lifeStone;
	SmartAnimationSequenceNode* healAnimation;
	CollisionObject* healCollision;
	WorldSound* healSound;
	
	bool isAnimating;
};
