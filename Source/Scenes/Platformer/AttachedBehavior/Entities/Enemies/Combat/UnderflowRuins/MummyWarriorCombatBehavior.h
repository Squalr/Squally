#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class MummyWarriorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MummyWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MummyWarriorCombatBehavior(GameObject* owner);
	virtual ~MummyWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
