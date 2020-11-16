#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class SquallyCombatBehaviorGroup : public EntityCombatBehaviorBase
{
public:
	static SquallyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCombatBehaviorGroup(GameObject* owner);
	virtual ~SquallyCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityCombatBehaviorBase super;
};
