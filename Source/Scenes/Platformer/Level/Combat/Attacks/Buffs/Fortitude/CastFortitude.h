#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

namespace cocos2d
{
	class Sprite;
};

class WorldSound;

class CastFortitude : public PlatformerAttack
{
public:
	static CastFortitude* create(float attackDuration, float recoverDuration, Priority priority);

	bool isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastFortitude(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastFortitude();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	WorldSound* castSound;
};
