#pragma once

#include "Engine/Components/Component.h"

class PlatformerEnemy;
class Sound;

class EnemyCombatEngageBehavior : public Component
{
public:
	static EnemyCombatEngageBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyCombatEngageBehavior(GameObject* owner);
	virtual ~EnemyCombatEngageBehavior();
	
	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void stopAllEntityActions();
	void engageEnemy(bool firstStrike);

	bool canEngage;

	PlatformerEnemy* enemy;
	Sound* engageSound;
};
