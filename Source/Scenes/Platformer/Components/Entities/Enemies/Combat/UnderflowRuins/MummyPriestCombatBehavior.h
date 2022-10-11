#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class MummyPriestCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MummyPriestCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MummyPriestCombatBehavior(GameObject* owner);
	virtual ~MummyPriestCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
