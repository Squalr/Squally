#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class WerewolfCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static WerewolfCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	WerewolfCombatBehavior(GameObject* owner);
	virtual ~WerewolfCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
