#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class TikiGolemCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static TikiGolemCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TikiGolemCombatBehavior(GameObject* owner);
	virtual ~TikiGolemCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
