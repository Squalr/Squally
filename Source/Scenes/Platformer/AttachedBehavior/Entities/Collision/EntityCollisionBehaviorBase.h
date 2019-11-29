#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

class CollisionObject;
class PlatformerEntity;

class EntityCollisionBehaviorBase : public AttachedBehavior
{
public:
	CollisionObject* entityCollision;

protected:
	EntityCollisionBehaviorBase(GameObject* owner, PlatformerCollisionType collisionType);
	~EntityCollisionBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
};
