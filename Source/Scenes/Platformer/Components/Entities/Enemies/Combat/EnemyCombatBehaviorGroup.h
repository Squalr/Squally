#pragma once

#include "Engine/Components/ComponentGroup.h"

class EnemyCombatBehaviorGroup : public ComponentGroup
{
public:
	static EnemyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyCombatBehaviorGroup(GameObject* owner);
	virtual ~EnemyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
