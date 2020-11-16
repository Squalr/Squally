#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class GuanoCombatBehaviorGroup : public EntityCombatBehaviorBase
{
public:
	static GuanoCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoCombatBehaviorGroup(GameObject* owner);
	virtual ~GuanoCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityCombatBehaviorBase super;
};
