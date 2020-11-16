#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityDisableCollisionBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
