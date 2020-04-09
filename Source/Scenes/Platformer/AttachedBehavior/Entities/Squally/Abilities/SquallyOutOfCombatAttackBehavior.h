#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class Projectile;
class Squally;
class Weapon;

class SquallyOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:
	static SquallyOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~SquallyOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	Projectile* createProjectile() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation();
	std::string getOutOfCombatAttackSound();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();
	Weapon* getWeapon();
	Projectile* createProjectile(std::function<Projectile*()> createFunc);

	Projectile* projectile;

	Squally* squally;
};
