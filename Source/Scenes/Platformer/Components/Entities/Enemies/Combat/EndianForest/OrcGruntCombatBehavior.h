#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class OrcGruntCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OrcGruntCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcGruntCombatBehavior(GameObject* owner);
	virtual ~OrcGruntCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;

	PlatformerEntity* entity;
};
