#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class GuanoAttackBehavior : public Component
{
public:
	static GuanoAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoAttackBehavior(GameObject* owner);
	virtual ~GuanoAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
};
