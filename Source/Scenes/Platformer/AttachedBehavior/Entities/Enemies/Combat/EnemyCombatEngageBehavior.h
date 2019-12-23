#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEnemy;

class EnemyCombatEngageBehavior : public AttachedBehavior
{
public:
	static EnemyCombatEngageBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EnemyCombatEngageBehavior(GameObject* owner);
	~EnemyCombatEngageBehavior();
	
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void stopAllEntityActions();
	void engageEnemy(bool firstStrike);

	bool canEngage;

	PlatformerEnemy* enemy;
};
