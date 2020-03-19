#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class EntityCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCombatBehaviorGroup(GameObject* owner);
	virtual ~EntityCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
