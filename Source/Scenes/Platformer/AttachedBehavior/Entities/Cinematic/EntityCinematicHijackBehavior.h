#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityCinematicHijackBehavior : public AttachedBehavior
{
public:
	static EntityCinematicHijackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCinematicHijackBehavior(GameObject* owner);
	virtual ~EntityCinematicHijackBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
