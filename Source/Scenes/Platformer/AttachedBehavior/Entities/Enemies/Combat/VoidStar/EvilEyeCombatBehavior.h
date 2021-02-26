#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class EvilEyeCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static EvilEyeCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EvilEyeCombatBehavior(GameObject* owner);
	virtual ~EvilEyeCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
