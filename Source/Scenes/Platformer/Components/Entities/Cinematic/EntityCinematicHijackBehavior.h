#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityCinematicHijackBehavior : public Component
{
public:
	static EntityCinematicHijackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCinematicHijackBehavior(GameObject* owner);
	virtual ~EntityCinematicHijackBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
};
