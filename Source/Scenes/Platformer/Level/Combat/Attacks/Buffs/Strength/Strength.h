#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

class Strength : public Buff
{
public:
	static Strength* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string StrengthIdentifier;

protected:
	Strength(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Strength();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDelt(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target) override;

private:
	typedef Buff super;

	void applyStrength();
	
	volatile int currentDamageDelt;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const int MinMultiplier;
	static const int MaxMultiplier;
	static const int DamageIncrease;
	static const float Duration;
};
