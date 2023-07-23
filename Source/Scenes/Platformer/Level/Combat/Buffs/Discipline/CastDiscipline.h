#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastDiscipline : public PlatformerAttack
{
public:
	static CastDiscipline* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;

protected:
	CastDiscipline(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastDiscipline();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* disciplineSound = nullptr;
};
