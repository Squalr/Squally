#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class TigressCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static TigressCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TigressCombatBehavior(GameObject* owner);
	virtual ~TigressCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
