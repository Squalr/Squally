#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ScarecrowCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ScarecrowCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScarecrowCombatBehavior(GameObject* owner);
	virtual ~ScarecrowCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
