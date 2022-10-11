#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityCinematicHijackBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
