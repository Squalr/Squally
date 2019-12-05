#pragma once

#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"

namespace cocos2d
{
	class PhysicsBody;
};

class PlatformerEntity;

class Projectile : public CollisionObject
{
public:
	void launchTowardsTarget(Node* target, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float spinSpeed = 0.0f, cocos2d::Vec3 secondsPer256pxLinearDistance = cocos2d::Vec3(0.75f, 0.75f, 0.75f), cocos2d::Vec3 gravity = cocos2d::Vec3(0.0f, -768.0f, 0.0f));
	void setLaunchVelocity(cocos2d::Vec3 velocity);
	void setLaunchAcceleration(cocos2d::Vec3 acceleration);
	cocos2d::Vec3 getLaunchVelocity();
	cocos2d::Vec3 getLaunchAcceleration();
	
protected:
	Projectile(PlatformerEntity* caster, cocos2d::PhysicsBody* hitBox, CombatCollisionType combatCollisionType, float noCollideDuration, bool allowHacking);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	virtual HackablePreview* createVelocityPreview();
	virtual HackablePreview* createAccelerationPreview();
	
	PlatformerEntity* caster;

private:
	typedef CollisionObject super;

	float radius;
	float spinSpeed;
	bool allowHacking;
	cocos2d::Vec3 launchVelocity;
	cocos2d::Vec3 launchAcceleration;
	float noCollideDuration;
};
