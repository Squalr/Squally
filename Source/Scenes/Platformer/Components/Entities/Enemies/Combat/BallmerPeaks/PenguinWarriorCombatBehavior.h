#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class PenguinWarriorCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static PenguinWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	PenguinWarriorCombatBehavior(GameObject* owner);
	virtual ~PenguinWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
