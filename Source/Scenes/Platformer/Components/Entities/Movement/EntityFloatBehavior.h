#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityFloatBehavior : public GameComponent
{
public:
	static EntityFloatBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string MapPropertyDeathSinkHeight;

protected:
	EntityFloatBehavior(GameObject* owner);
	virtual ~EntityFloatBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	float elapsed = 0.0f;
	float deathElapsed = 0.0f;
	float deathSinkHeight = 0.0f;
};
