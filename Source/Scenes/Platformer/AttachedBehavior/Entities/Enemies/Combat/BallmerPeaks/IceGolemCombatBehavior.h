#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class IceGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static IceGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	IceGolemCombatBehavior(GameObject* owner);
	virtual ~IceGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
