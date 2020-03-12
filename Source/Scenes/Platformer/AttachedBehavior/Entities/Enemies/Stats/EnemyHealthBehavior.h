#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEnemy;

class EnemyHealthBehavior : public AttachedBehavior
{
public:
	static EnemyHealthBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;
	static const std::string SaveKeyIsDead;

protected:
	EnemyHealthBehavior(GameObject* owner);
	virtual ~EnemyHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
