#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class EarthElementalCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static EarthElementalCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EarthElementalCombatBehavior(GameObject* owner);
	virtual ~EarthElementalCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
