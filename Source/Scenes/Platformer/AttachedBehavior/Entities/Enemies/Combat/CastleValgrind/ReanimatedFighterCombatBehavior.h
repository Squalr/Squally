#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ReanimatedFighterCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ReanimatedFighterCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ReanimatedFighterCombatBehavior(GameObject* owner);
	virtual ~ReanimatedFighterCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
