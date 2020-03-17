#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowIncrementHealthFlask : public PlatformerAttack
{
public:
	static ThrowIncrementHealthFlask* create();

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowIncrementHealthFlask();
	virtual ~ThrowIncrementHealthFlask();

	bool isWorthUsing(const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound;
};
