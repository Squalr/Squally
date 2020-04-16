#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class Projectile;
class KingGrogg;
class SmartAnimationSequenceNode;
class Weapon;

class GroggOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:
	static GroggOutOfCombatAttackBehavior* create(GameObject* owner);

	void attack();

	static const std::string MapKey;

protected:
	GroggOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~GroggOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	Projectile* createProjectile() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation();
	std::string getOutOfCombatAttackSound();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();

	Projectile* projectile;
	SmartAnimationSequenceNode* fireBreath;

	KingGrogg* kingGrogg;
};
