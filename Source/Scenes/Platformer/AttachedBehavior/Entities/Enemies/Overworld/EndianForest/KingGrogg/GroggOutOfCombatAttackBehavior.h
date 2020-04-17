#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Overworld/EnemyOutOfCombatAttackBehavior.h"

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
	
	std::string getOutOfCombatAttackAnimation();
	std::string getOutOfCombatAttackSound();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();
	
	SmartAnimationSequenceNode* fireBreath;

	KingGrogg* kingGrogg;
};
