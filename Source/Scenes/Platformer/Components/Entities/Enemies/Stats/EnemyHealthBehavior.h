#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEnemy;

class EnemyHealthBehavior : public GameComponent
{
public:
	static EnemyHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string SaveKeyIsDead;

protected:
	EnemyHealthBehavior(GameObject* owner);
	virtual ~EnemyHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEnemy* entity;
};
