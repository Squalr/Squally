#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityGroundCollisionBehavior : public AttachedBehavior
{
public:
	static EntityGroundCollisionBehavior* create(GameObject* owner);

	void onCollideWithGround();
	bool isOnGround();
	bool isStandingOn(CollisionObject* collisonObject);
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	
	CollisionObject* groundCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityGroundCollisionBehavior(GameObject* owner);
	~EntityGroundCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionHeight;
	static const float GroundCollisionRadius;
};
