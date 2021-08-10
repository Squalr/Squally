#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyCombatRespawnBehavior : public GameComponent
{
public:
	static SquallyCombatRespawnBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCombatRespawnBehavior(GameObject* owner);
	virtual ~SquallyCombatRespawnBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void respawn(bool softRevive);

	Squally* squally;
};
