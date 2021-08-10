#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityDisableCollisionBehavior : public GameComponent
{
public:
	static EntityDisableCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityDisableCollisionBehavior(GameObject* owner);
	virtual ~EntityDisableCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
};
