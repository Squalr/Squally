#pragma once

#include "Entities/Platformer/Attacks/PlatformerAttack.h"

class BasicSlash : public PlatformerAttack
{
public:
	static BasicSlash* create(float attackDuration, float recoverDuration);

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;

protected:
	BasicSlash(float attackDuration, float recoverDuration);
	~BasicSlash() = default;

private:
	typedef PlatformerAttack super;
};
