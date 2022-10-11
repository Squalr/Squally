#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class EntityGroundCollisionBehavior;
class EntityHeadCollisionBehavior;
class EntityMovementBehavior;
class PlatformerEntity;
class WorldSound;

class EntityCollisionBehaviorBase : public GameComponent
{
public:
	void enableStandingPhysics();
	void enableNormalPhysics();
	void enableWaterPhysics();
	void setIsAlivePhysics(bool isAlive);
	void setMountPhysics(bool isMounted);
	cocos2d::Vec2 getGravity();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	bool hasLeftWallCollision();
	bool hasRightWallCollision();
	bool hasLeftWallCollisionWith(CollisionObject* collisonObject);
	bool hasRightWallCollisionWith(CollisionObject* collisonObject);
	bool isOnGround();
	
	CollisionObject* entityCollision = nullptr;
	CollisionObject* movementCollision = nullptr;
	CollisionObject* leftCollision = nullptr;
	CollisionObject* rightCollision = nullptr;

protected:
	EntityCollisionBehaviorBase(GameObject* owner, int collisionType, int collisionTypeMovement);
	virtual ~EntityCollisionBehaviorBase();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	virtual void onEntityCollisionCreated() = 0;

	PlatformerEntity* entity = nullptr;

private:
	typedef GameComponent super;
	
	void warpToPosition(cocos2d::Vec3 position, bool warpCamera);
	void buildEntityCollision();
	void buildMovementCollision();
	void buildWallDetectors();
	virtual void tryBind();

	EntityGroundCollisionBehavior* groundCollision = nullptr;
	EntityHeadCollisionBehavior* headCollision = nullptr;
	EntityMovementBehavior* movementBehavior = nullptr;
	bool movementCollisionBound = false;
	float noEmergeSubmergeSoundCooldown = 1.0f;
	int collisionType = 0;
	int collisionTypeMovement = 0;
	WorldSound* submergeSound = nullptr;
	WorldSound* emergeSound = nullptr;

	static const float WaterJumpVelocity;
	static const float SwimVerticalDrag;
	static const float StaticFriction;
};
