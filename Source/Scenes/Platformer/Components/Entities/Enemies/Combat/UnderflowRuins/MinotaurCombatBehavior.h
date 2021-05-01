#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class MinotaurCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MinotaurCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MinotaurCombatBehavior(GameObject* owner);
	virtual ~MinotaurCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
