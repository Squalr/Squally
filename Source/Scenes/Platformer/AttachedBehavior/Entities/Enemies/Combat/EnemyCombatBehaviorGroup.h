#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class EnemyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EnemyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyCombatBehaviorGroup(GameObject* owner);
	virtual ~EnemyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
