#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ForestGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ForestGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ForestGolemCombatBehavior(GameObject* owner);
	virtual ~ForestGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
