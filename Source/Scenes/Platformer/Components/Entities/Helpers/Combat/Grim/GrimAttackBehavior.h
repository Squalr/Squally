#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerAttack;
class PlatformerEntity;

class GrimAttackBehavior : public GameComponent
{
public:
	static GrimAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimAttackBehavior(GameObject* owner);
	virtual ~GrimAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
