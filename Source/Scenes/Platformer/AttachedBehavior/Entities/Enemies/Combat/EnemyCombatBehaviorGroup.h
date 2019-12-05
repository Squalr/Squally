#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class EnemyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EnemyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EnemyCombatBehaviorGroup(GameObject* owner);
	~EnemyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
