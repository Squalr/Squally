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

class StoneSkin : public Buff
{
public:
	static StoneSkin* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string StoneSkinIdentifier;

protected:
	StoneSkin(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~StoneSkin();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing) override;

private:
	typedef Buff super;

	void applyStoneSkin();
	
	volatile int currentDamageTaken;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* bubble;
	cocos2d::Sprite* spellAura;
	
	static const int MaxMultiplier;
	static const float Duration;
};
