#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;

class Defend : public Buff
{
public:
	static Defend* create(PlatformerEntity* caster, bool isDistractActiveParam);
	
	bool isDistractActive();

protected:
	Defend(PlatformerEntity* caster, bool isDistractActiveParam);
	virtual ~Defend();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset) override;

private:
	typedef Buff super;

	void onDamageTakenOrCycle(bool isDamage);

	bool isDistractActiveParam = false;
	cocos2d::Sprite* defendEffect = nullptr;
	int resetCount = 0;

	static const float DamageReduction;
};
