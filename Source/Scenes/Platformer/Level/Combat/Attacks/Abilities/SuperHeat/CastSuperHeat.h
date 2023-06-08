#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastSuperHeat : public PlatformerAttack
{
public:
	static CastSuperHeat* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	CastSuperHeat(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastSuperHeat();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* superHeatSound = nullptr;
};
