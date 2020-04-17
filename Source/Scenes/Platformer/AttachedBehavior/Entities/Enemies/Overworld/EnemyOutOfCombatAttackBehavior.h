#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class PlatformerEnemy;
class Projectile;

class EnemyOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:

protected:
	EnemyOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~EnemyOutOfCombatAttackBehavior();

	void decorateProjectile(Projectile* projectile) override;

private:
	typedef EntityOutOfCombatAttackBehavior super;

	PlatformerEnemy* enemy;
};
