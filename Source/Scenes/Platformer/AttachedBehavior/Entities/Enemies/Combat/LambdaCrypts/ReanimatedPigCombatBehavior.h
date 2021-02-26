#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ReanimatedPigCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ReanimatedPigCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ReanimatedPigCombatBehavior(GameObject* owner);
	virtual ~ReanimatedPigCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
