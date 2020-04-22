#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class DoubleSlash : public PlatformerAttack
{
public:
	static DoubleSlash* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay = 0.25f);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	DoubleSlash(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay);
	virtual ~DoubleSlash();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;
	float weaveDelay;
};
