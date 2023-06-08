#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastDefend : public PlatformerAttack
{
public:
	static CastDefend* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;

protected:
	CastDefend(Priority priority);
	virtual ~CastDefend();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	virtual void onAttackStaged() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* defendSound = nullptr;
};
