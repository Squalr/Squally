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
	static EntityGroundCollisionBehavior* create(GameObject* owner);

	void onCollideWithGround();
	bool isOnGround();
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
	static const float GroundCollisionRadius;
};
