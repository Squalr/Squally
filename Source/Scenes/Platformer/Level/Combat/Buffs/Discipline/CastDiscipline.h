#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastDiscipline : public PlatformerAttack
{
public:
	static CastDiscipline* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;

protected:
	CastDiscipline(Priority priority);
	virtual ~CastDiscipline();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	virtual void onAttackStaged() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* disciplineSound = nullptr;
};
