#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class OrcBomberCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OrcBomberCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcBomberCombatBehavior(GameObject* owner);
	virtual ~OrcBomberCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
