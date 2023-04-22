#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class CollisionObject;
class PlatformerEntity;
class SmartAnimationNode;

class Catapult : public InteractObject
{
public:
	static Catapult* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

	void setUsingBombs(bool isUsingBombs);
	void launchCatapult();

protected:
	Catapult(cocos2d::ValueMap& properties);
	virtual ~Catapult();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity);
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef InteractObject super;

	void returnToIdle();
	void launchBall();
	cocos2d::Vec2 applyLaunchPower(cocos2d::Vec2 baseSpeed);

	SmartAnimationNode* catapultAnimations = nullptr;
	AnimationPart* ballAnimationPart = nullptr;
	bool interactionEnabled = false;
	float currentCooldown = 0.0f;
	float launchPower = 0.0f;
	bool isUsingBombs = false;

	static const float InteractCooldown;
	static const float LaunchPowerDefault;
	static const cocos2d::Vec2 LaunchVelocityBase;
};
