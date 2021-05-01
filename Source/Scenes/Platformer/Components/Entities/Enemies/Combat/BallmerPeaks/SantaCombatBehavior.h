#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SantaCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static SantaCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SantaCombatBehavior(GameObject* owner);
	virtual ~SantaCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
