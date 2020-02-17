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
	bool hasLeftCornerCollision();
	bool hasRightCornerCollision();
	bool isStandingOn(CollisionObject* collisonObject);
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	
	CollisionObject* leftCornerCollision;
	CollisionObject* rightCornerCollision;
	CollisionObject* groundCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityGroundCollisionBehavior(GameObject* owner);
	virtual ~EntityGroundCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void buildGroundCollisionDetector();
	void buildCornerCollisionDetectors();

	PlatformerEntity* entity;

	float detectorWidth;

	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionHeight;
	static const float GroundCollisionRadius;
	static const float CornerCollisionWidth;
};
