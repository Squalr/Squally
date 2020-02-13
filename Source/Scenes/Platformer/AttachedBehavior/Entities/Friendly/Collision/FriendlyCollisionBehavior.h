#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class CollisionObject;
class PlatformerEntity;

class FriendlyCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyCollisionBehavior* create(GameObject* owner);

	CollisionObject* entityCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyCollisionBehavior(GameObject* owner);
	virtual ~FriendlyCollisionBehavior();

	void onLoad() override;
	void onEntityCollisionCreated() override;

private:
	typedef EntityCollisionBehaviorBase super;
};
