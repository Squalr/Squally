#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class CollisionObject;
class PlatformerEntity;
class Portal;
class SmartAnimationNode;
class Squally;
class WorldSound;

class Cannon : public MountBase
{
public:
	static Cannon* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

	void launchCannon();

protected:
	Cannon(cocos2d::ValueMap& properties);
	virtual ~Cannon();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;
	cocos2d::Vec2 getReparentPosition() override;
	void update(float) override;

private:
	typedef MountBase super;

	void returnToIdle();
	void launchBall();
	cocos2d::Vec2 applyLaunchPower(cocos2d::Vec2 baseSpeed);

	SmartAnimationNode* cannonAnimations = nullptr;
	AnimationPart* ballAnimationPart = nullptr;
	bool interactionEnabled = false;
	float currentCooldown = 0.0f;
	float launchPower = 0.0f;
	WorldSound* shootSound = nullptr;
	Portal* skyPortal = nullptr;
	
	bool isLaunching = false;
	Vec2 currentMountOffset;

	Squally* squally = nullptr;

	static const float InteractCooldown;
	static const cocos2d::Vec2 LaunchVelocity;
};
