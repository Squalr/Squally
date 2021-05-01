#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyCombatRespawnBehavior : public Component
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
	typedef Component super;
	
	void respawn(bool softRevive);

	Squally* squally;
};
