#pragma once

#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EnemyOutOfCombatAttackBehavior.h"

class Projectile;
class KingGrogg;
class SmartAnimationSequenceNode;
class Weapon;

class GroggOutOfCombatAttackBehavior : public EnemyOutOfCombatAttackBehavior
{
public:
	static GroggOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GroggOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~GroggOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	Projectile* createProjectile() override;

private:
	typedef EnemyOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;
	
	SmartAnimationSequenceNode* fireBreath;

	KingGrogg* kingGrogg;
};
