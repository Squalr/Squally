#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityDisarmedBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
