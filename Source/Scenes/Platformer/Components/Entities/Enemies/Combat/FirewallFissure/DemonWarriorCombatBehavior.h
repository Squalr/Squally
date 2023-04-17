#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonWarriorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonWarriorCombatBehavior(GameObject* owner);
	virtual ~DemonWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
