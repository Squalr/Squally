#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class AbominationCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AbominationCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AbominationCombatBehavior(GameObject* owner);
	virtual ~AbominationCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
