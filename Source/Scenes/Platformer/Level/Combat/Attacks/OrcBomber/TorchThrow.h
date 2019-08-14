#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class TorchThrow : public PlatformerAttack
{
public:
	static TorchThrow* create(float attackDuration, float recoverDuration);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	TorchThrow(float attackDuration, float recoverDuration);
	~TorchThrow();

	void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
};
