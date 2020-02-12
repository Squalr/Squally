#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class Tent : public HackableObject
{
public:
	static Tent* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTent;

protected:
	Tent(cocos2d::ValueMap& properties);
	virtual ~Tent();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	void runHealAnimation(bool reRun = false);
	std::vector<cocos2d::Vec2> createTentTopCollision();

	cocos2d::Sprite* tentBack;
	SmartAnimationSequenceNode* healAnimation;
	cocos2d::Sprite* tentFront;
	CollisionObject* topCollision;
	CollisionObject* healCollision;
	WorldSound* healSound;
	
	bool isAnimating;
};
