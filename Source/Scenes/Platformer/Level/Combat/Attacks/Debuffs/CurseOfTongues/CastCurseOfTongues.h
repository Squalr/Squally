#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class CastCurseOfTongues : public PlatformerAttack
{
public:
	static CastCurseOfTongues* create(float attackDuration, float recoverDuration, Priority priority);

	bool isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	float getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastCurseOfTongues(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastCurseOfTongues();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	WorldSound* castSound;
};
