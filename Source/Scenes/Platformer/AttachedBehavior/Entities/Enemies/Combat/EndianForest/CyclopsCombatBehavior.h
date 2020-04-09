#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

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
