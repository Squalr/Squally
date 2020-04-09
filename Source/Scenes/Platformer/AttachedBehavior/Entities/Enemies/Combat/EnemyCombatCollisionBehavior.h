#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class CollisionObject;
class PlatformerEntity;

class EnemyCombatCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static EnemyCombatCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyCombatCollisionBehavior(GameObject* owner);
	virtual ~EnemyCombatCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void onEntityCollisionCreated() override;

private:
	typedef EntityCollisionBehaviorBase super;

	PlatformerEntity* entity;
};
