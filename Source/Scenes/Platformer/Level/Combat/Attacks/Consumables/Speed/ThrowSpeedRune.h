#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class Sound;

class ThrowSpeedRune : public PlatformerAttack
{
public:
	static ThrowSpeedRune* create();

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowSpeedRune();
	~ThrowSpeedRune();

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	Sound* throwSound;
};
