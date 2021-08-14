#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityRunBehavior : public GameComponent
{
public:
	static EntityRunBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityRunBehavior(GameObject* owner);
	virtual ~EntityRunBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;

	static const float RunAcceleration;
};
