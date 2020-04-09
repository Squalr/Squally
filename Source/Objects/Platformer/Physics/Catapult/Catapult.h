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
	static Catapult* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

	void launchCatapult();

protected:
	Catapult(cocos2d::ValueMap& properties);
	virtual ~Catapult();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void launchBall();
	cocos2d::Vec2 applyLaunchPower(cocos2d::Vec2 baseSpeed);

	SmartAnimationNode* catapultAnimations;
	CollisionObject* catapultCollision;
	AnimationPart* ballAnimationPart;
	bool interactionEnabled;
	float currentCooldown;
	float launchPower;

	static const float InteractCooldown;
	static const float LaunchPowerDefault;
	static const cocos2d::Vec2 LaunchVelocityBase;
};
