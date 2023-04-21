#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class PerceptronCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static PerceptronCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	PerceptronCombatBehavior(GameObject* owner);
	virtual ~PerceptronCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
