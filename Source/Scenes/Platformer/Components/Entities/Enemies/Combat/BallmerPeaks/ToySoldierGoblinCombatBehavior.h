#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ToySoldierGoblinCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ToySoldierGoblinCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ToySoldierGoblinCombatBehavior(GameObject* owner);
	virtual ~ToySoldierGoblinCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
