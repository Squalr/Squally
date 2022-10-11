#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class VikingCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static VikingCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	VikingCombatBehavior(GameObject* owner);
	virtual ~VikingCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
