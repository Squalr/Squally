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

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target, std::function<void(PlatformerEntity* target)> onTargetHit) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
};
