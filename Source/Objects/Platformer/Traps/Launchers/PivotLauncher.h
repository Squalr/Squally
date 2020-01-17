#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class HackableData;
class PlatformerEntity;
class Projectile;
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
	virtual Projectile* createProjectile() = 0;

	ProjectilePool* projectilePool;

private:
	typedef HackableObject super;
	
	void shoot();
	void faceTarget();
	void updateShootTimer(float dt);

	float timeSinceLastShot;
	cocos2d::Node* containerNode;
	SmartAnimationNode* launcherAnimations;
	AnimationPart* cannon;

	PlatformerEntity* target;
	std::string targetQueryKey;

	static const std::string PivotBone;

	static const std::string PropertyLaunchSpeed;
	static const std::string PropertyPivotTarget;
	static const float DefaultLaunchSpeed;
	static const float LaunchCooldownMin;
	static const float LaunchCooldownMax;
};
