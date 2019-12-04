#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerEntity;

class Projectile : public HackableObject
{
public:
	void launchTowardsTarget(Node* target, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float spinSpeed = 0.0f, cocos2d::Vec3 secondsPer256pxLinearDistance = cocos2d::Vec3(0.75f, 0.75f, 0.75f), cocos2d::Vec3 gravity = cocos2d::Vec3(0.0f, -768.0f, 0.0f));
	void setVelocity(cocos2d::Vec3 velocity);
	void setAcceleration(cocos2d::Vec3 acceleration);
	cocos2d::Vec3 getVelocity();
	cocos2d::Vec3 getAcceleration();
	
protected:
	Projectile(PlatformerEntity* caster, float radius, float noCollideDuration, bool allowHacking);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	virtual HackablePreview* createVelocityPreview();
	virtual HackablePreview* createAccelerationPreview();
	virtual void onCollideWithTarget(PlatformerEntity* target) = 0;
	
	PlatformerEntity* caster;
	cocos2d::Node* contentNode;

private:
	typedef HackableObject super;

	float radius;
	bool allowHacking;
	cocos2d::Vec3 velocity;
	cocos2d::Vec3 acceleration;
	bool hasCollided;
	float noCollideDuration;
	float elapsedDuration;
};
