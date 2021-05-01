#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class AgnesCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AgnesCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AgnesCombatBehavior(GameObject* owner);
	virtual ~AgnesCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
