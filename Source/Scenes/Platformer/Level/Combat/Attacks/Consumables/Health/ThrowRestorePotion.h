#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class Sound;

class ThrowRestorePotion : public PlatformerAttack
{
public:
	static ThrowRestorePotion* create();

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowRestorePotion();
	~ThrowRestorePotion();

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	Sound* throwSound;
};
