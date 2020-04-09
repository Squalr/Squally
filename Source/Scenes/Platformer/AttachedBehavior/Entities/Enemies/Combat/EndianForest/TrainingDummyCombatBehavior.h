#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class TrainingDummyCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static TrainingDummyCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TrainingDummyCombatBehavior(GameObject* owner);
	virtual ~TrainingDummyCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
