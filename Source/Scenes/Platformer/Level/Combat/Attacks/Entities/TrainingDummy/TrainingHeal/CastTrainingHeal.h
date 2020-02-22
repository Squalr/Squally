#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class CastTrainingHeal : public PlatformerAttack
{
public:
	static CastTrainingHeal* create(float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastTrainingHeal(float attackDuration, float recoverDuration, float priority);
	virtual ~CastTrainingHeal();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
};
