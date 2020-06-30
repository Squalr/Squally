#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowIncrementHealthFlask : public PlatformerAttack
{
public:
	static ThrowIncrementHealthFlask* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowIncrementHealthFlask(Priority priority);
	virtual ~ThrowIncrementHealthFlask();

	bool isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound;
};
