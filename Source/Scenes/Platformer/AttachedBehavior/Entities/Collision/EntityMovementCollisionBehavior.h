#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityMovementCollisionBehavior : public AttachedBehavior
{
public:
	static EntityMovementCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	bool hasLeftWallCollision();
	bool hasRightWallCollision();
	
	CollisionObject* movementCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityMovementCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityMovementCollisionBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	void buildMovementCollision();
	void buildWallDetectors();

	PlatformerEntity* entity;
	CollisionObject* leftCollision;
	CollisionObject* rightCollision;

	static const float WallDetectorSize;
	static const float WaterJumpVelocity;
	static const float SwimVerticalDrag;
};
