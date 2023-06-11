#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastDistract : public PlatformerAttack
{
public:
	static CastDistract* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;

protected:
	CastDistract(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastDistract();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* defendSound = nullptr;
};
