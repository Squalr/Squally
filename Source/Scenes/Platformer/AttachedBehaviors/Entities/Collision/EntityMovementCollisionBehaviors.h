#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityMovementCollisionBehaviors : public AttachedBehavior
{
public:
	static EntityMovementCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityMovementCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityMovementCollisionBehaviors();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	CollisionObject* movementCollision;
};
