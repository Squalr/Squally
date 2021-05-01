#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SnowFiendCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SnowFiendCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SnowFiendCombatBehavior(GameObject* owner);
	virtual ~SnowFiendCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
