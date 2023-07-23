#pragma once

#include "Scenes/Platformer/Components/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class PlatformerEnemy;
class Projectile;
class Squally;

class EnemyOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:

protected:
	EnemyOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~EnemyOutOfCombatAttackBehavior();

	void onEnter() override;
	void decorateProjectile(Projectile* projectile) override;

private:
	typedef EntityOutOfCombatAttackBehavior super;

	PlatformerEnemy* enemy = nullptr;
	Squally* squally = nullptr;
};
