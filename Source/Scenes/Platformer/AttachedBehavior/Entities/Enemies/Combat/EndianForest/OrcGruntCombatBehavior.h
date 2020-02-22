#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class OrcGruntCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OrcGruntCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcGruntCombatBehavior(GameObject* owner);
	virtual ~OrcGruntCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;

	PlatformerEntity* entity;
};
