#pragma once

#include "Engine/Components/GameComponentGroup.h"

class EntityCombatBehaviorGroup : public GameComponentGroup
{
public:
	static EntityCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCombatBehaviorGroup(GameObject* owner);
	virtual ~EntityCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
