#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Axe;
class Bow;
class EntityAttackBehavior;
class EntityInventoryBehavior;
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

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyAttackBehavior(GameObject* owner);
	virtual ~SquallyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void loadWeaponAttacks(EntityAttackBehavior* attackBehavior);
	void loadUnarmedAttacks(EntityAttackBehavior* attackBehavior);
	void loadAxeAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Axe* sword);
	void loadBowAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Bow* sword);
	void loadMaceAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Mace* sword);
	void loadSpearAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Spear* sword);
	void loadSwordAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Sword* sword);
	void loadWandAttacks(EntityAttackBehavior* attackBehavior,EntityInventoryBehavior* inventoryBehavior, Wand* sword);

	std::tuple<int, int> computeWeaponDamageRange(Weapon* weapon, EntityInventoryBehavior* inventoryBehavior);

	Squally* squally;
};
