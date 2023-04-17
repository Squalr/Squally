#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonArcherCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonArcherCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonArcherCombatBehavior(GameObject* owner);
	virtual ~DemonArcherCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
