#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class Squally;
class Weapon;

class SquallyOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:
	static SquallyOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~SquallyOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation();
	std::string getOutOfCombatAttackSound();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();
	Weapon* getWeapon();

	Squally* squally;
};
