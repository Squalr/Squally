#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class VampireLordCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static VampireLordCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	VampireLordCombatBehavior(GameObject* owner);
	virtual ~VampireLordCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
