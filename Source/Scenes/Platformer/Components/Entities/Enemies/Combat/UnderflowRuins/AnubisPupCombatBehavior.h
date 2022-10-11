#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class AnubisPupCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AnubisPupCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AnubisPupCombatBehavior(GameObject* owner);
	virtual ~AnubisPupCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
