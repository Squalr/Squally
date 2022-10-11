#pragma once

#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"

class CollisionObject;

class FriendlyCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyCollisionBehavior* create(GameObject* owner);

	CollisionObject* entityCollision;

	static const std::string MapKey;

protected:
	FriendlyCollisionBehavior(GameObject* owner);
	virtual ~FriendlyCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void onEntityCollisionCreated() override;

private:
	typedef EntityCollisionBehaviorBase super;
};
