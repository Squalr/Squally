#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityDisarmedBehavior : public Component
{
public:
	static EntityDisarmedBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityDisarmedBehavior(GameObject* owner);
	virtual ~EntityDisarmedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
};
