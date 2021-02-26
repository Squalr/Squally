#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class GargoyleCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GargoyleCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GargoyleCombatBehavior(GameObject* owner);
	virtual ~GargoyleCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
