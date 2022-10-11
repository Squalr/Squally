#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class EarthGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static EarthGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EarthGolemCombatBehavior(GameObject* owner);
	virtual ~EarthGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
