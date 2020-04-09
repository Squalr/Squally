#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class EntityGroundCollisionBehavior;
class EntityHeadCollisionBehavior;
class EntityMovementBehavior;
class PlatformerEntity;
class WorldSound;

class EntityDummyMovementCollisionBehavior : public AttachedBehavior
{
public:
	static EntityDummyMovementCollisionBehavior* create(GameObject* owner);
	
	CollisionObject* movementCollision;

	static const std::string MapKey;

protected:
	EntityDummyMovementCollisionBehavior(GameObject* owner);
	virtual ~EntityDummyMovementCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void buildMovementCollision();

	PlatformerEntity* entity;
};
