#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class PenguinGruntCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static PenguinGruntCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	PenguinGruntCombatBehavior(GameObject* owner);
	virtual ~PenguinGruntCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
