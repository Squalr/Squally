#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class UndeadCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static UndeadCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	UndeadCombatBehavior(GameObject* owner);
	virtual ~UndeadCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
