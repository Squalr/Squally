#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class ThrowFlamingWeapon : public PlatformerAttack
{
public:
	static ThrowFlamingWeapon* create(float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	ThrowFlamingWeapon(float attackDuration, float recoverDuration, float priority);
	~ThrowFlamingWeapon();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
};
