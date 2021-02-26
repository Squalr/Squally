#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalPirateCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalPirateCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalPirateCombatBehavior(GameObject* owner);
	virtual ~SkeletalPirateCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
