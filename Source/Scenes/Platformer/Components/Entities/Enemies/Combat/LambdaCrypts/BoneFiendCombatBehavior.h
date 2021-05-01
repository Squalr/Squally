#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class BoneFiendCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static BoneFiendCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BoneFiendCombatBehavior(GameObject* owner);
	virtual ~BoneFiendCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
