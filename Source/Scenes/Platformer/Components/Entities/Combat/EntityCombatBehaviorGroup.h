#pragma once

#include "Engine/Components/ComponentGroup.h"

class EntityCombatBehaviorGroup : public ComponentGroup
{
public:
	static EntityCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCombatBehaviorGroup(GameObject* owner);
	virtual ~EntityCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
