#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityDisableMovementCollisionBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
