#pragma once

#include "Engine/Components/Component.h"

class PlatformerEnemy;

class EnemyHealthBehavior : public Component
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
	typedef Component super;

	PlatformerEnemy* entity;
};
