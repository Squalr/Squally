#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ZombieElricCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ZombieElricCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ZombieElricCombatBehavior(GameObject* owner);
	virtual ~ZombieElricCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
