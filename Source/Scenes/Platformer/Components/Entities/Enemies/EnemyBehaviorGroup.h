#pragma once

#include "Engine/Components/ComponentGroup.h"

class EnemyBehaviorGroup : public ComponentGroup
{
public:
	static EnemyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBehaviorGroup(GameObject* owner);
	virtual ~EnemyBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
