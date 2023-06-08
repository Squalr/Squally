#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;

class Discipline : public Buff
{
public:
	static Discipline* create(PlatformerEntity* caster);

protected:
	Discipline(PlatformerEntity* caster);
	virtual ~Discipline();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset) override;

private:
	typedef Buff super;

	void onDamageTakenOrCycle(bool isDamage);

	cocos2d::Sprite* disciplineEffect = nullptr;
	int resetCount = 0;
};
