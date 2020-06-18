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

class SharpenedBlade : public Buff
{
public:
	static SharpenedBlade* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string SharpenedBladeIdentifier;
	static const std::string HackIdentifierSharpenedBlade;

protected:
	SharpenedBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SharpenedBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applySharpenedBlade();
	
	volatile int currentDamageDelt;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const int MaxMultiplier;
	static const float Duration;
};
