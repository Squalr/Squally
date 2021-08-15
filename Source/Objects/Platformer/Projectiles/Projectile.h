#pragma once

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Hackables/HackableObject.h"

class PlatformerEntity;

class Projectile : public HackableObject
{
public:
	enum class MovementMode
	{
		Kinematic,
		RotationVelocity,
	};

	MovementMode getMovementMode();
	void setMovementMode(MovementMode movementMode);
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	void launchTowardsTarget(Node* target, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float spinSpeed = 0.0f, cocos2d::Vec2 secondsPer256pxLinearDistance = cocos2d::Vec2(0.75f, 0.75f), cocos2d::Vec2 gravity = cocos2d::Vec2(0.0f, -768.0f));
	void launchTowardsTarget3D(Node* target, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float spinSpeed = 0.0f, cocos2d::Vec3 secondsPer256pxLinearDistance = cocos2d::Vec3(0.75f, 0.75f, 0.75f), cocos2d::Vec3 gravity = cocos2d::Vec3(0.0f, -768.0f, 0.0f));
	void setLaunchVelocity(cocos2d::Vec3 velocity);
	void setLaunchAcceleration(cocos2d::Vec3 acceleration);
	void setProjectileRotation(float projectileRotation);
	float getProjectileRotation();
	CollisionObject* getCollision();
	cocos2d::Vec3 getLaunchVelocity();
	cocos2d::Vec3 getLaunchAcceleration();
	void setSpeedMultiplier(cocos2d::Vec3 speedMultiplier);
	bool isEnabled();
	void enable(bool setVisible);
	void disable(bool setVisible);
	void addDecor(cocos2d::Node* decor);
	void clearDecor();
	virtual void runSpawnFX();
	virtual void runImpactFX();

	static const std::string ProjectileTag;
	
protected:
	Projectile(PlatformerEntity* caster, std::vector<cocos2d::Vec2> hitBox, int collisionType, bool allowHacking);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	virtual HackablePreview* createVelocityPreview();
	virtual HackablePreview* createAccelerationPreview();
	void enableUpdate();
	void disableUpdate();
	
	bool canUpdate = true;
	
	PlatformerEntity* caster = nullptr;
	CollisionObject* collisionObject = nullptr;
	cocos2d::Node* contentNode = nullptr;
	cocos2d::Node* decorNode = nullptr;
	cocos2d::Node* postFXNode = nullptr;

private:
	typedef HackableObject super;

	MovementMode movementMode = MovementMode::Kinematic;

	CollisionObject* ownerCollisionRef = nullptr;
	cocos2d::Node* rotationNode = nullptr;
	float spinSpeed = 0.0f;
	float projectileRotation = 0.0f;
	float noOwnerCollideDuration = 1.0f;
	bool enabled = true;
	bool allowHacking = false;
	cocos2d::Vec3 launchVelocity = cocos2d::Vec3::ZERO;
	cocos2d::Vec3 launchAcceleration = cocos2d::Vec3::ZERO;
	cocos2d::Vec3 speedMultiplier = cocos2d::Vec3::ONE;
};
