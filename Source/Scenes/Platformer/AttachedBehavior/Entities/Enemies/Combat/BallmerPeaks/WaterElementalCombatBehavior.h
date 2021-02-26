#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class WaterElementalCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static WaterElementalCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	WaterElementalCombatBehavior(GameObject* owner);
	virtual ~WaterElementalCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
