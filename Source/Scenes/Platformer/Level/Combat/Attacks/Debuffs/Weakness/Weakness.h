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

class Weakness : public Buff
{
public:
	static Weakness* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string WeaknessIdentifier;

protected:
	Weakness(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Weakness();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDelt(CombatEvents::ModifyableDamageOrHealing damageOrHealing) override;

private:
	typedef Buff super;

	void applyWeakness();
	
	volatile int currentDamageDelt;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const int MinMultiplier;
	static const int MaxMultiplier;
	static const int DamageIncrease;
	static const float Duration;
};
