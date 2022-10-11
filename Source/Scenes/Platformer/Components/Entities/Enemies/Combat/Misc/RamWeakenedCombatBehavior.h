#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class SaveTownLine;

class RamWeakenedCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static RamWeakenedCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RamWeakenedCombatBehavior(GameObject* owner);
	virtual ~RamWeakenedCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;

	SaveTownLine* saveTownLine;
};
