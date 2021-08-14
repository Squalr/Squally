#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEnemy;
class Sound;

class EnemyCombatEngageBehavior : public GameComponent
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
	typedef GameComponent super;

	void stopAllEntityActions();
	void engageEnemy(bool firstStrike);

	bool canEngage = true;

	PlatformerEnemy* enemy = nullptr;
	Sound* engageSound = nullptr;
};
