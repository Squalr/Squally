#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class GoblinGruntBoarCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GoblinGruntBoarCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinGruntBoarCombatBehavior(GameObject* owner);
	virtual ~GoblinGruntBoarCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
