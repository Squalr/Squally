#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class LazarusCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static LazarusCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LazarusCombatBehavior(GameObject* owner);
	virtual ~LazarusCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
