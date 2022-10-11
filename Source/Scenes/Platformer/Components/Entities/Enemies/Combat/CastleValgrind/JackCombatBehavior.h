#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class JackCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static JackCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	JackCombatBehavior(GameObject* owner);
	virtual ~JackCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
