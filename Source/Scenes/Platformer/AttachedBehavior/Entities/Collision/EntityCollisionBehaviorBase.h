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
	~EntityCollisionBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
};
