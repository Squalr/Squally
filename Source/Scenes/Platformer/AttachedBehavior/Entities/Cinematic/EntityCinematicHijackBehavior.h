#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityCinematicHijackBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
