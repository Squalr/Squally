#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class TorchThrow : public PlatformerAttack
{
public:
	static TorchThrow* create(float attackDuration, float recoverDuration);

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;

protected:
	TorchThrow(float attackDuration, float recoverDuration);
	~TorchThrow() = default;

private:
	typedef PlatformerAttack super;

	void spawnProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
};
