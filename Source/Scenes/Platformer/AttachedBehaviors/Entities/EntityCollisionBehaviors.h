#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityCollisionBehaviors : public AttachedBehavior
{
public:
	static EntityCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCollisionBehaviors();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	float calculateGhettoOffsetFix();

	PlatformerEntity* entity;
	CollisionObject* groundCollision;

	static const float GroundCollisionPadding;
};
