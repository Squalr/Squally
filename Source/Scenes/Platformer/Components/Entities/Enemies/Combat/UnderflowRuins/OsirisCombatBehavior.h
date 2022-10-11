#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class OsirisCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OsirisCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OsirisCombatBehavior(GameObject* owner);
	virtual ~OsirisCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
