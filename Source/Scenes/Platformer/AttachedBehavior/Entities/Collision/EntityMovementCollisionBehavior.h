#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityMovementCollisionBehavior : public AttachedBehavior
{
public:
	static EntityMovementCollisionBehavior* create(GameObject* owner);

	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	bool hasLeftWallCollision();
	bool hasRightWallCollision();
	
	CollisionObject* movementCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityMovementCollisionBehavior(GameObject* owner);
	~EntityMovementCollisionBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	void buildMovementCollision();
	void buildWallDetectors();
	void tryBind();

	PlatformerEntity* entity;
	CollisionObject* leftCollision;
	CollisionObject* rightCollision;

	bool movementCollisionBound;

	static const float WaterJumpVelocity;
	static const float SwimVerticalDrag;
};
