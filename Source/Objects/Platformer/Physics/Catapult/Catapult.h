#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class SmartAnimationNode;
class CollisionObject;

class Catapult : public HackableObject
{
public:
	static Catapult* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCatapult;

protected:
	Catapult(cocos2d::ValueMap& initProperties);
	virtual ~Catapult();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	SmartAnimationNode* catapultAnimations;
	CollisionObject* catapultCollision;

	bool interactionEnabled;
	float currentCooldown;
	AnimationPart* ballAnimationPart;

	static const float InteractCooldown;
};
