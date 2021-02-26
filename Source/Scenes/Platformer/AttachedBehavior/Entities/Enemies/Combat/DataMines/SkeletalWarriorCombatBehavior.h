#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalWarriorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalWarriorCombatBehavior(GameObject* owner);
	virtual ~SkeletalWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
