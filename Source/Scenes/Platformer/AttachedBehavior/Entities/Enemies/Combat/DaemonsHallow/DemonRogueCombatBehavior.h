#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonRogueCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonRogueCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonRogueCombatBehavior(GameObject* owner);
	virtual ~DemonRogueCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
