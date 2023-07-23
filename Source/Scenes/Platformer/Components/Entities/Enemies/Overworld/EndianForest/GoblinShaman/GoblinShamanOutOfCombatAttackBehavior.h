#pragma once

#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EnemyOutOfCombatAttackBehavior.h"

class AgroBehavior;
class PlatformerEnemy;
class Projectile;
class SmartAnimationSequenceNode;
class Weapon;

class GoblinShamanOutOfCombatAttackBehavior : public EnemyOutOfCombatAttackBehavior
{
public:
	static GoblinShamanOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinShamanOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~GoblinShamanOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	Projectile* createProjectile() override;

private:
	typedef EnemyOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;
	float getOutOfCombatAttackCooldown() override;
	float getProjectileLifetime() override;
	
	SmartAnimationSequenceNode* shadowBolt = nullptr;
	PlatformerEnemy* goblinShaman = nullptr;
	AgroBehavior* agroBehavior = nullptr;
};
