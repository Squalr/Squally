#pragma once

#include "Scenes/Platformer/Components/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

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
	void decorateProjectile(Projectile* projectile) override;
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	Weapon* getWeapon();

	Projectile* projectile;

	Squally* squally;
};
