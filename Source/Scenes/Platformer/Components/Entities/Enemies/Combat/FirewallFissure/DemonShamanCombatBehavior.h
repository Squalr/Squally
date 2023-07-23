#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonShamanCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonShamanCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonShamanCombatBehavior(GameObject* owner);
	virtual ~DemonShamanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
