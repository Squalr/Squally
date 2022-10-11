#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class RhinomanCombatBeahvior : public EntityCombatBehaviorBase
{
public:
	static RhinomanCombatBeahvior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RhinomanCombatBeahvior(GameObject* owner);
	virtual ~RhinomanCombatBeahvior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
