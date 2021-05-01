#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class TrollCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static TrollCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TrollCombatBehavior(GameObject* owner);
	virtual ~TrollCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
