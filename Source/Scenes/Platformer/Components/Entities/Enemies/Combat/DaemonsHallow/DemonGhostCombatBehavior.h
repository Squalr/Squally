#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonGhostCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonGhostCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonGhostCombatBehavior(GameObject* owner);
	virtual ~DemonGhostCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
