#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class VoidArcherCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static VoidArcherCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	VoidArcherCombatBehavior(GameObject* owner);
	virtual ~VoidArcherCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
