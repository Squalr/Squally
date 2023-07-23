#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonDragonCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonDragonCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonDragonCombatBehavior(GameObject* owner);
	virtual ~DemonDragonCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
