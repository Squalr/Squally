#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ShadeCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ShadeCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShadeCombatBehavior(GameObject* owner);
	virtual ~ShadeCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
