#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyCombatRespawnBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;
	
	void respawn();

	Squally* squally;
};
