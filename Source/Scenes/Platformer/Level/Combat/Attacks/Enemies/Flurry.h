#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class Flurry : public PlatformerAttack
{
public:
	static Flurry* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	Flurry(float attackDuration, float recoverDuration, Priority priority);
	virtual ~Flurry();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;
};
