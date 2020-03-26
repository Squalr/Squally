#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

namespace cocos2d
{
	class Sprite;
};

class WorldSound;

class CastReflect : public PlatformerAttack
{
public:
	static CastReflect* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastReflect(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastReflect();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	bool isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	cocos2d::Sprite* spellAura;
	WorldSound* castSound;
};
