#pragma once

#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EnemyOutOfCombatAttackBehavior.h"

class AgroBehavior;
class Projectile;
class MainhandThrow;
class SmartAnimationSequenceNode;
class Weapon;

class MainhandThrowOutOfCombatAttackBehavior : public EnemyOutOfCombatAttackBehavior
{
public:
	static MainhandThrowOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MainhandThrowOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~MainhandThrowOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;
	float getOutOfCombatAttackCooldown() override;
	float getProjectileLifetime() override;
	Projectile* createProjectile() override;

private:
	typedef EnemyOutOfCombatAttackBehavior super;
	
	AgroBehavior* agroBehavior = nullptr;
	PlatformerEntity* owner = nullptr;
};
