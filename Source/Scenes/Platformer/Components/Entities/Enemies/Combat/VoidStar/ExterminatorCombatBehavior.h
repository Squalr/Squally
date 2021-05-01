#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ExterminatorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ExterminatorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ExterminatorCombatBehavior(GameObject* owner);
	virtual ~ExterminatorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
