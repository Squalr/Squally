#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class CryogenCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static CryogenCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CryogenCombatBehavior(GameObject* owner);
	virtual ~CryogenCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
