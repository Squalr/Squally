#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class EntityAttackBehavior;
class PlatformerAttack;
class Squally;

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

	Squally* squally;
};
