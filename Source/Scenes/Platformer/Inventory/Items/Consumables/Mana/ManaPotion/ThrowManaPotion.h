#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowManaPotion : public PlatformerAttack
{
public:
	static ThrowManaPotion* create(Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowManaPotion(Priority priority);
	virtual ~ThrowManaPotion();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound;
};
