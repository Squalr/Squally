#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalArcherCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalArcherCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalArcherCombatBehavior(GameObject* owner);
	virtual ~SkeletalArcherCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
