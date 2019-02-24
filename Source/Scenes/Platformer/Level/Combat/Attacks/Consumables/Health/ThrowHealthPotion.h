#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class ThrowHealthPotion : public PlatformerAttack
{
public:
	static ThrowHealthPotion* create();

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	ThrowHealthPotion();
	virtual ~ThrowHealthPotion();

private:
	typedef PlatformerAttack super;

	void spawnProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
};
