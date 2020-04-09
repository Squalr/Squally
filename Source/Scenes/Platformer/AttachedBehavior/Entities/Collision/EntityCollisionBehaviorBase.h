#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityCollisionBehaviorBase : public AttachedBehavior
{
public:
	CollisionObject* entityCollision;

protected:
	EntityCollisionBehaviorBase(GameObject* owner, int collisionType);
	virtual ~EntityCollisionBehaviorBase();

	void onLoad() override;
	void onDisable() override;
	virtual void onEntityCollisionCreated() = 0;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	int collisionType;

	void buildEntityCollision();
};
