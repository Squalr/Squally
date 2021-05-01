#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SkeletalBaronCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SkeletalBaronCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SkeletalBaronCombatBehavior(GameObject* owner);
	virtual ~SkeletalBaronCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
