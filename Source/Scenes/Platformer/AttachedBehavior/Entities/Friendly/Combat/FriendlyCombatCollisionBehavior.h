#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class PlatformerEntity;

class FriendlyCombatCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyCombatCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyCombatCollisionBehavior(GameObject* owner);
	virtual ~FriendlyCombatCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void onEntityCollisionCreated() override;

private:
	typedef EntityCollisionBehaviorBase super;

	PlatformerEntity* owner;
};
