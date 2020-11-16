#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class EnemyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EnemyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBehaviorGroup(GameObject* owner);
	virtual ~EnemyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
