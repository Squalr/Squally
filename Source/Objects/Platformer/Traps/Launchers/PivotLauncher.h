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
	void setAutoLaunch(bool isAutoLaunch);

	static const std::string HackIdentifierLaunchTimer;

protected:
	PivotLauncher(cocos2d::ValueMap& properties, std::string animationResource, int projectilePoolCapacity);
	virtual ~PivotLauncher();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	virtual Projectile* createProjectile() = 0;
	virtual cocos2d::Vec2 getProjectileSpawnPosition();
	virtual HackablePreview* getTimerPreview();

	ProjectilePool* projectilePool = nullptr;

	float currentAngle = 0.0f;
	float launchSpeed = 0.0f;

private:
	typedef HackableObject super;
	
	void shoot();
	bool rangeCheck();
	void faceTarget();
	void updateShootTimer(float dt);

	float launchTimer = 0.0f;
	cocos2d::Node* containerNode = nullptr;
	SmartAnimationNode* launcherAnimations = nullptr;
	AnimationPart* cannon = nullptr;

	PlatformerEntity* target = nullptr;
	std::string targetQueryKey;
	
	float fixedAngle = 0.0f;
	bool isFixed = false;
	bool is3DEnabled = false;
	bool isAutoLaunch = true;

	static const std::string PivotBone;
	static const std::string PropertyLaunchSpeed;
	static const std::string PropertyPivotTarget;
	static const std::string PropertyFixed;
	static const std::string PropertyEnable3D;
	static const float DefaultLaunchSpeed;
	static const float LaunchCooldownMin;
	static const float LaunchCooldownMax;
};
