#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityCinematicHijackBehavior : public AttachedBehavior
{
public:
	static EntityCinematicHijackBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCinematicHijackBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCinematicHijackBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
