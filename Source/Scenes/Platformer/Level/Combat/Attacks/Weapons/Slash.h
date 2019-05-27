#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class Slash : public PlatformerAttack
{
public:
	static Slash* create(float attackDuration, float recoverDuration);

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	Slash(float attackDuration, float recoverDuration);
	~Slash() = default;

	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
};
