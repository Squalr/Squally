#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class FrostFiendCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static FrostFiendCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FrostFiendCombatBehavior(GameObject* owner);
	virtual ~FrostFiendCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
