#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityDisableMovementCollisionBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity;
};
