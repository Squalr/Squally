#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class MultiShot2 : public PlatformerAttack
{
public:
	static MultiShot2* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay = 0.25f);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	MultiShot2(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay);
	virtual ~MultiShot2();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound = nullptr;
	WorldSound* hitSound = nullptr;
	float weaveDelay = 0.0f;
};
