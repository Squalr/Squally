#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class CentaurCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static CentaurCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CentaurCombatBehavior(GameObject* owner);
	virtual ~CentaurCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
