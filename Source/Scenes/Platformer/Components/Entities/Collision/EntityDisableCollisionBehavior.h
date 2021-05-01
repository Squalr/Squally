#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityDisableCollisionBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
