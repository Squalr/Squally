#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class AssassinCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AssassinCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AssassinCombatBehavior(GameObject* owner);
	virtual ~AssassinCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
