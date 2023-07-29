#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class PlatformerEntity;

class EntityKillableBehavior : public GameComponent
{
public:
	static EntityKillableBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityKillableBehavior(GameObject* owner);
	virtual ~EntityKillableBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
