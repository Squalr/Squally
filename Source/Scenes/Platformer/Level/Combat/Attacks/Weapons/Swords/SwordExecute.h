#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class SwordExecute : public PlatformerAttack
{
public:
	static SwordExecute* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	SwordExecute(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority);
	virtual ~SwordExecute();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;

	static const float SwordExecuteBonus;
};
