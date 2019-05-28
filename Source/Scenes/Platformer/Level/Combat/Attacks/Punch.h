#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class Sound;

class Punch : public PlatformerAttack
{
public:
	static Punch* create(float attackDuration, float recoverDuration);

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	Punch(float attackDuration, float recoverDuration);
	~Punch() = default;

	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;

	Sound* punchSound;
};
