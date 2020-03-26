#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class DropBomb : public PlatformerAttack
{
public:
	static DropBomb* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	DropBomb(float attackDuration, float recoverDuration, Priority priority);
	virtual ~DropBomb();

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
};
