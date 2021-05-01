#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class GorillaCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GorillaCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GorillaCombatBehavior(GameObject* owner);
	virtual ~GorillaCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
