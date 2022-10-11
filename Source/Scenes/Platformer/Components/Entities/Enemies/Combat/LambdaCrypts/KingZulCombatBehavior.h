#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class KingZulCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static KingZulCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KingZulCombatBehavior(GameObject* owner);
	virtual ~KingZulCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
