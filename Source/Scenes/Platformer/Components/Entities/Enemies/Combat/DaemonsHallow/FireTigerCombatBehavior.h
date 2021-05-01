#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class FireTigerCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static FireTigerCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FireTigerCombatBehavior(GameObject* owner);
	virtual ~FireTigerCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
