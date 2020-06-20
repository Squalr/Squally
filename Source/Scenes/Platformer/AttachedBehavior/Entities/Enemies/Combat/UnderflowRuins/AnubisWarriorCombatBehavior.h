#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class AnubisWarriorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AnubisWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AnubisWarriorCombatBehavior(GameObject* owner);
	virtual ~AnubisWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
