#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class GoblinGruntBoarCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GoblinGruntBoarCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GoblinGruntBoarCombatBehavior(GameObject* owner);
	virtual ~GoblinGruntBoarCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
