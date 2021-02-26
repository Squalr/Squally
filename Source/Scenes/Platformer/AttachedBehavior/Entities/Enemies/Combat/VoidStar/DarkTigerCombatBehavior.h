#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class DarkTigerCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DarkTigerCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DarkTigerCombatBehavior(GameObject* owner);
	virtual ~DarkTigerCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
