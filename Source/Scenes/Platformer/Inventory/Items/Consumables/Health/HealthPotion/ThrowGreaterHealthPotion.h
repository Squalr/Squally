#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowGreaterHealthPotion : public PlatformerAttack
{
public:
	static ThrowGreaterHealthPotion* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowGreaterHealthPotion(Priority priority);
	virtual ~ThrowGreaterHealthPotion();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound;
	WorldSound* healSound;
};
