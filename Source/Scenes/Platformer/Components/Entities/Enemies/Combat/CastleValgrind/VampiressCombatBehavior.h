#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class VampiressCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static VampiressCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	VampiressCombatBehavior(GameObject* owner);
	virtual ~VampiressCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
