#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowGreaterManaPotion : public PlatformerAttack
{
public:
	static ThrowGreaterManaPotion* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowGreaterManaPotion(Priority priority);
	virtual ~ThrowGreaterManaPotion();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound = nullptr;
};
