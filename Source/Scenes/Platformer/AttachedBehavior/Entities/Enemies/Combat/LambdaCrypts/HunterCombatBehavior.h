#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class HunterCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static HunterCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HunterCombatBehavior(GameObject* owner);
	virtual ~HunterCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
