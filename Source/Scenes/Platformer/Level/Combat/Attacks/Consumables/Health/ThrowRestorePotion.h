#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class ThrowRestorePotion : public PlatformerAttack
{
public:
	static ThrowRestorePotion* create();

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	ThrowRestorePotion();
	~ThrowRestorePotion();

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
};
