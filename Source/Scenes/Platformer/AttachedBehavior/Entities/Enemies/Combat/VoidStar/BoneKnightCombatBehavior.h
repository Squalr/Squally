#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class BoneKnightCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static BoneKnightCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BoneKnightCombatBehavior(GameObject* owner);
	virtual ~BoneKnightCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
