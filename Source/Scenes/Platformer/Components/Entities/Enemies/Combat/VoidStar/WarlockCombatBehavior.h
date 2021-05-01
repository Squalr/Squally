#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class WarlockCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static WarlockCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	WarlockCombatBehavior(GameObject* owner);
	virtual ~WarlockCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
