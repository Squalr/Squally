#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class GuanoAttackBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
