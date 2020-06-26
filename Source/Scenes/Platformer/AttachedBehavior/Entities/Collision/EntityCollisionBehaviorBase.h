#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class EntityGroundCollisionBehavior;
class EntityHeadCollisionBehavior;
class EntityMovementBehavior;
class PlatformerEntity;
class WorldSound;

class EntityCollisionBehaviorBase : public AttachedBehavior
{
public:

	void enableNormalPhysics();
	void enableWaterPhysics();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	bool hasLeftWallCollision();
	bool hasRightWallCollision();
	bool hasLeftWallCollisionWith(CollisionObject* collisonObject);
	bool hasRightWallCollisionWith(CollisionObject* collisonObject);
	
	CollisionObject* entityCollision;
	CollisionObject* leftCollision;
	CollisionObject* rightCollision;

protected:
	EntityCollisionBehaviorBase(GameObject* owner, int collisionType);
	virtual ~EntityCollisionBehaviorBase();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	virtual void onEntityCollisionCreated() = 0;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
	
	void warpToPosition(cocos2d::Vec3 position, bool warpCamera);
	void buildEntityCollision();
	void buildWallDetectors();
	void tryBind();

	EntityGroundCollisionBehavior* groundCollision;
	EntityHeadCollisionBehavior* headCollision;
	EntityMovementBehavior* movementBehavior;
	bool entityCollisionBound;
	float noEmergeSubmergeSoundCooldown;
	int collisionType;
	WorldSound* submergeSound;
	WorldSound* emergeSound;

	static const float WaterJumpVelocity;
	static const float SwimVerticalDrag;
	static const float StaticFriction;
};
