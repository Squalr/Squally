#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastVanish : public PlatformerAttack
{
public:
	static CastVanish* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;

protected:
	CastVanish(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastVanish();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* sfx = nullptr;
};
