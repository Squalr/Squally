#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class Clippy;
class HackableData;
class PlatformerEntity;
class Projectile;
class ProjectilePool;
class SmartAnimationNode;

class PivotLauncher : public HackableObject
{
public:
	void setAutoLaunch(bool isAutoLaunch);

protected:
	PivotLauncher(cocos2d::ValueMap& properties, std::string animationResource, int projectilePoolCapacity);
	virtual ~PivotLauncher();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	virtual Projectile* createProjectile() = 0;
	virtual Clippy* getTimerClippy();
	virtual HackablePreview* getTimerPreview();

	ProjectilePool* projectilePool;

	float currentAngle;
	float launchSpeed;

private:
	typedef HackableObject super;
	
	void shoot();
	bool rangeCheck();
	void faceTarget();
	void updateShootTimer(float dt);

	float launchTimer;
	cocos2d::Node* containerNode;
	SmartAnimationNode* launcherAnimations;
	AnimationPart* cannon;

	PlatformerEntity* target;
	std::string targetQueryKey;
	
	float fixedAngle;
	bool isFixed;
	bool isAutoLaunch;

	static const std::string PivotBone;
	static const std::string PropertyLaunchSpeed;
	static const std::string PropertyPivotTarget;
	static const std::string PropertyFixed;
	static const float DefaultLaunchSpeed;
	static const float LaunchCooldownMin;
	static const float LaunchCooldownMax;
};
