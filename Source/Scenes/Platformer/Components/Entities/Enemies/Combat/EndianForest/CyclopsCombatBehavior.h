#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class CyclopsCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static CyclopsCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CyclopsCombatBehavior(GameObject* owner);
	virtual ~CyclopsCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
