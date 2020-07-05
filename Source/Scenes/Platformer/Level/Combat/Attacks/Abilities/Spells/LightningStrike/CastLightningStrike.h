#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastLightningStrike : public PlatformerAttack
{
public:
	static CastLightningStrike* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	CastLightningStrike(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastLightningStrike();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* lightningSound;
};
