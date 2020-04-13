#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowHealthPotion : public PlatformerAttack
{
public:
	static ThrowHealthPotion* create(Priority priority, float healPercentage, std::string iconResource);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowHealthPotion(Priority priority, float healPercentage, std::string iconResource);
	virtual ~ThrowHealthPotion();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	float healPercentage;

	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound;
	WorldSound* healSound;
};
