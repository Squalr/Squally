#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ThugCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ThugCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ThugCombatBehavior(GameObject* owner);
	virtual ~ThugCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
