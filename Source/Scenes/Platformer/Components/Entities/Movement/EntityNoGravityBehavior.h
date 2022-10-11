#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class PlatformerEntity;

class EntityNoGravityBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
