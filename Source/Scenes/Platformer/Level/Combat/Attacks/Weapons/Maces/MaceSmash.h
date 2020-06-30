#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class MaceSmash : public PlatformerAttack
{
public:
	static MaceSmash* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	MaceSmash(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);
	virtual ~MaceSmash();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;

	static const float DamageMultiplier;
};
