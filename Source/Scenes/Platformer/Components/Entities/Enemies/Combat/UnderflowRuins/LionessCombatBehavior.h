#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class LionessCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static LionessCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LionessCombatBehavior(GameObject* owner);
	virtual ~LionessCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
