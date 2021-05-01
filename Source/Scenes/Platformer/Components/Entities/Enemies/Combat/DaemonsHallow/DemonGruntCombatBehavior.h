#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonGruntCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonGruntCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonGruntCombatBehavior(GameObject* owner);
	virtual ~DemonGruntCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
