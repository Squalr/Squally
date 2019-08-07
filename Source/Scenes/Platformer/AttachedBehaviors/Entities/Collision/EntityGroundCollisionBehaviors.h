#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityGroundCollisionBehaviors : public AttachedBehavior
{
public:
	static EntityGroundCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	bool isOnGround();
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityGroundCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityGroundCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	CollisionObject* groundCollision;

	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionRadius;
};
