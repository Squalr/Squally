#pragma once

#include "Engine/Components/Component.h"

class CollisionObject;
class PlatformerEntity;

class EntityNoGravityBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
