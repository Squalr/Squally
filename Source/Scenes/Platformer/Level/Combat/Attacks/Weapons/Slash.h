#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class Slash : public PlatformerAttack
{
public:
	static Slash* create(float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	Slash(float attackDuration, float recoverDuration, float priority);
	~Slash() = default;

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;
};
