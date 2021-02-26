#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class AsmodeusCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static AsmodeusCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AsmodeusCombatBehavior(GameObject* owner);
	virtual ~AsmodeusCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
