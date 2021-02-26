#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalNecromancerCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalNecromancerCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalNecromancerCombatBehavior(GameObject* owner);
	virtual ~SkeletalNecromancerCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
