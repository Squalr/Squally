#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class YetiCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static YetiCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	YetiCombatBehavior(GameObject* owner);
	virtual ~YetiCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
