#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityDisableMovementCollisionBehavior : public AttachedBehavior
{
public:
	static EntityDisableMovementCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityDisableMovementCollisionBehavior(GameObject* owner);
	virtual ~EntityDisableMovementCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
