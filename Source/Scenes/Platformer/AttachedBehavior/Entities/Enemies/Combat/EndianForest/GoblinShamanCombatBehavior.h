#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class GoblinShamanCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static GoblinShamanCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinShamanCombatBehavior(GameObject* owner);
	virtual ~GoblinShamanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
