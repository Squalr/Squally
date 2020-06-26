#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class EntityGroundCollisionBehavior;
class EntityHeadCollisionBehavior;
class EntityMovementBehavior;
class PlatformerEntity;
class WorldSound;

class EntityMovementCollisionBehavior : public AttachedBehavior
{
public:
	static EntityMovementCollisionBehavior* create(GameObject* owner);
	
	CollisionObject* movementCollision;

	static const std::string MapKey;

protected:
	EntityMovementCollisionBehavior(GameObject* owner);
	virtual ~EntityMovementCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	void buildMovementCollision();
};
