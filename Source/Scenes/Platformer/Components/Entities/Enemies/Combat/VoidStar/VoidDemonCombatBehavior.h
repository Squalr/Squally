#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class VoidDemonCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static VoidDemonCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	VoidDemonCombatBehavior(GameObject* owner);
	virtual ~VoidDemonCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
