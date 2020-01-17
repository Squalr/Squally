#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class HackableData;
class ProjectilePool;
class SmartAnimationNode;

class PivotLauncher : public HackableObject
{
public:

protected:
	PivotLauncher(cocos2d::ValueMap& properties, std::string animationResource);
	virtual ~PivotLauncher();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;
	void shoot(float dt);

	float timeSinceLastShot;
	ProjectilePool* projectilePool;
	SmartAnimationNode* launcherAnimations;
	AnimationPart* cannon;
	cocos2d::Node* projectileNode;

	static const std::string PivotBone;

	static const std::string PropertyLaunchSpeed;
	static const float DefaultLaunchSpeed;
	static const float LaunchCooldownMin;
	static const float LaunchCooldownMax;
};
