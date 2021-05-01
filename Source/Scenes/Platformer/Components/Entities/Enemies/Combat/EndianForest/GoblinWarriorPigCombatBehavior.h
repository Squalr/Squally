#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class GoblinWarriorPigCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GoblinWarriorPigCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinWarriorPigCombatBehavior(GameObject* owner);
	virtual ~GoblinWarriorPigCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
