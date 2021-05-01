#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityRunBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;

	static const float RunAcceleration;
};
