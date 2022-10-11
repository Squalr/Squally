#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalKnightCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalKnightCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalKnightCombatBehavior(GameObject* owner);
	virtual ~SkeletalKnightCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
