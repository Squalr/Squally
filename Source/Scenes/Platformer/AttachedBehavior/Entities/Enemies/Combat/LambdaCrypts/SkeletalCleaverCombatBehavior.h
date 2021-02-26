#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalCleaverCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalCleaverCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalCleaverCombatBehavior(GameObject* owner);
	virtual ~SkeletalCleaverCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
