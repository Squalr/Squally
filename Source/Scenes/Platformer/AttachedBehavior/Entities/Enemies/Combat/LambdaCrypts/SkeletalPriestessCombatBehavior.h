#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalPriestessCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalPriestessCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalPriestessCombatBehavior(GameObject* owner);
	virtual ~SkeletalPriestessCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
