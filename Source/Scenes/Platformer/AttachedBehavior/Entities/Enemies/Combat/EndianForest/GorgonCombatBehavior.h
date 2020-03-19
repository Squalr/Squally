#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class GorgonCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GorgonCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GorgonCombatBehavior(GameObject* owner);
	virtual ~GorgonCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
