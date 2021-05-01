#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class MedusaCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MedusaCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MedusaCombatBehavior(GameObject* owner);
	virtual ~MedusaCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
