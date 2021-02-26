#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class MysticCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MysticCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MysticCombatBehavior(GameObject* owner);
	virtual ~MysticCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
