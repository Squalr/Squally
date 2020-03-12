#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEnemy;
class Sound;

class EnemyCombatEngageBehavior : public AttachedBehavior
{
public:
	static EnemyCombatEngageBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EnemyCombatEngageBehavior(GameObject* owner);
	virtual ~EnemyCombatEngageBehavior();
	
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void stopAllEntityActions();
	void engageEnemy(bool firstStrike);

	bool canEngage;

	PlatformerEnemy* enemy;
	Sound* engageSound;
};
