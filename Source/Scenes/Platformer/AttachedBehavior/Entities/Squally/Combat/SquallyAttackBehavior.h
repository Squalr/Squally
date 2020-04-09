#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Axe;
class Bow;
class EntityAttackBehavior;
class Mace;
class PlatformerAttack;
class Squally;
class Spear;
class Sword;
class Wand;
class Weapon;

class SquallyAttackBehavior : public AttachedBehavior
{
public:
	static SquallyAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyAttackBehavior(GameObject* owner);
	virtual ~SquallyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void loadWeaponAttacks(EntityAttackBehavior* attackBehavior);
	void loadUnarmedAttacks(EntityAttackBehavior* attackBehavior);
	void loadAxeAttacks(EntityAttackBehavior* attackBehavior, Axe* sword);
	void loadBowAttacks(EntityAttackBehavior* attackBehavior, Bow* sword);
	void loadMaceAttacks(EntityAttackBehavior* attackBehavior, Mace* sword);
	void loadSwordAttacks(EntityAttackBehavior* attackBehavior, Sword* sword);
	void loadWandAttacks(EntityAttackBehavior* attackBehavior, Wand* sword);

	std::tuple<int, int> computeWeaponDamageRange(Weapon* weapon);

	Squally* squally;
};
