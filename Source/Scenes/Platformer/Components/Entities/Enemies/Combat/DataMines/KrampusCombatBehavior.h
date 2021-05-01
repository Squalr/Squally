#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class KrampusCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static KrampusCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KrampusCombatBehavior(GameObject* owner);
	virtual ~KrampusCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
