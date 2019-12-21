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
	static Defend* create(PlatformerEntity* caster);

protected:
	Defend(PlatformerEntity* caster);
	~Defend();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeDamageTaken(int* damageOrHealing, bool* blocked, std::function<void()> handleCallback) override;
	void onTimelineReset(bool wasInterrupt) override;

private:
	typedef Buff super;

	void onDamageTakenOrCycle(bool isDamage);

	cocos2d::Sprite* defendEffect;

	int resetCount;

	static const float DamageReduction;
};
