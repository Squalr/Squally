#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastLifeSteal : public PlatformerAttack
{
public:
	static CastLifeSteal* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	CastLifeSteal(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastLifeSteal();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound = nullptr;
	WorldSound* hitSound = nullptr;

	static const float DamageMultiplier;
};
