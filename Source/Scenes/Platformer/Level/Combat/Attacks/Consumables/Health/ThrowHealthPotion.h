#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class Sound;

class ThrowHealthPotion : public PlatformerAttack
{
public:
	static ThrowHealthPotion* create();

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowHealthPotion();
	~ThrowHealthPotion();

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	PlatformerAttack* cloneInternal() override;

	Sound* throwSound;
};
