#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class FireElementalCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static FireElementalCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FireElementalCombatBehavior(GameObject* owner);
	virtual ~FireElementalCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
