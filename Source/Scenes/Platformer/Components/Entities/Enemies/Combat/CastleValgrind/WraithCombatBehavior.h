#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class WraithCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static WraithCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	WraithCombatBehavior(GameObject* owner);
	virtual ~WraithCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
