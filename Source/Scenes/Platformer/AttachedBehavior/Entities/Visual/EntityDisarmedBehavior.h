#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityDisarmedBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
