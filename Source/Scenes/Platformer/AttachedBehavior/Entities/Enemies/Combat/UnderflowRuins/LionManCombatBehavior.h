#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class LionManCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static LionManCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LionManCombatBehavior(GameObject* owner);
	virtual ~LionManCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
