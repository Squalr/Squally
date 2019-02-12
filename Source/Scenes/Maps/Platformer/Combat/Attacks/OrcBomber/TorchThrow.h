#pragma once

#include "Scenes/Maps/Platformer/Combat/Attacks/PlatformerAttack.h"

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

	void spawnProjectiles(PlatformerEntity* owner) override;
};
