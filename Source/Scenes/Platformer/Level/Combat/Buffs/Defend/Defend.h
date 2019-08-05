#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartAnimationSequenceNode;

class Defend : public Buff
{
public:
	static Defend* create(PlatformerEntity* caster);

protected:
	Defend(PlatformerEntity* caster);
	~Defend();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback) override;
	void onTimelineReset(bool wasInterrupt) override;

private:
	typedef Buff super;

	SmartAnimationSequenceNode* defendEffect;

	static const float DamageReduction;
};
