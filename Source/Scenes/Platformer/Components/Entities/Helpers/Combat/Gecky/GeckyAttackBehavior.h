#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerAttack;
class PlatformerEntity;

class GeckyAttackBehavior : public GameComponent
{
public:
	static GeckyAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyAttackBehavior(GameObject* owner);
	virtual ~GeckyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
};
