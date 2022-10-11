#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class LavaGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static LavaGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LavaGolemCombatBehavior(GameObject* owner);
	virtual ~LavaGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
