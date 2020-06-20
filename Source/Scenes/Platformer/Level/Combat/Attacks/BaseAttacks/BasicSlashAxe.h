#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class BasicSlashAxe : public PlatformerAttack
{
public:
	static BasicSlashAxe* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	BasicSlashAxe(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);
	virtual ~BasicSlashAxe();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;
};
