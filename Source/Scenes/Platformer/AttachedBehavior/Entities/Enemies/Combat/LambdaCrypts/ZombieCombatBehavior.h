#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ZombieCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ZombieCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ZombieCombatBehavior(GameObject* owner);
	virtual ~ZombieCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
