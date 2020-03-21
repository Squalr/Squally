#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class BowShoot : public PlatformerAttack
{
public:
	static BowShoot* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	BowShoot(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority);
	virtual ~BowShoot();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;
};
