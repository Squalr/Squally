#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class LightningGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static LightningGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LightningGolemCombatBehavior(GameObject* owner);
	virtual ~LightningGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
