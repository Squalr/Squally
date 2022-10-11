#pragma once

#include "Engine/Components/GameComponentGroup.h"

class EnemyCombatBehaviorGroup : public GameComponentGroup
{
public:
	static EnemyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyCombatBehaviorGroup(GameObject* owner);
	virtual ~EnemyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
