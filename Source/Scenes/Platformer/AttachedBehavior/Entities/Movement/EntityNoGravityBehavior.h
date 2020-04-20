#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityNoGravityBehavior : public AttachedBehavior
{
public:
	static EntityNoGravityBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityNoGravityBehavior(GameObject* owner);
	virtual ~EntityNoGravityBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
