#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityGroundCollisionBehavior : public AttachedBehavior
{
public:
	static EntityGroundCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	bool isOnGround();
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityGroundCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityGroundCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	CollisionObject* groundCollision;

	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionRadius;
};
