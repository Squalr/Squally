#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class OgreCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OgreCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OgreCombatBehavior(GameObject* owner);
	virtual ~OgreCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
