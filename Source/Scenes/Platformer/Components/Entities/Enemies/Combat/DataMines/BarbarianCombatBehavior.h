#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class BarbarianCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static BarbarianCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BarbarianCombatBehavior(GameObject* owner);
	virtual ~BarbarianCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
