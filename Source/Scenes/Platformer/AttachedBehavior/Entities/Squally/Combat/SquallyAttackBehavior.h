#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class EntityAttackBehavior;
class Squally;

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

	void loadSpellBookAttacks(EntityAttackBehavior* attackBehavior);
	void loadWeaponAttacks(EntityAttackBehavior* attackBehavior);
	void loadUnarmedAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);
	void loadAxeAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);
	void loadBowAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);
	void loadMaceAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);
	void loadSwordAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);
	void loadWandAttacks(EntityAttackBehavior* attackBehavior, int minAttack, int maxAttack);

	Squally* squally;
};
