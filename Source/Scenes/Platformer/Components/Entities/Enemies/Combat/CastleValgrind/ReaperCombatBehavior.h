#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class ReaperCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ReaperCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ReaperCombatBehavior(GameObject* owner);
	virtual ~ReaperCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
