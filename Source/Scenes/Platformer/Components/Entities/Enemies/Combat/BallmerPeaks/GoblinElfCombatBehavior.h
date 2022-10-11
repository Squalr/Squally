#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class GoblinElfCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GoblinElfCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinElfCombatBehavior(GameObject* owner);
	virtual ~GoblinElfCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
