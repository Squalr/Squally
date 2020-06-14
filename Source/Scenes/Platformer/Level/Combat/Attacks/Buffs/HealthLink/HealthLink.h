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

class HealthLink : public Buff
{
public:
	static HealthLink* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string HealthLinkIdentifier;

protected:
	HealthLink(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~HealthLink();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing) override;

private:
	typedef Buff super;
	friend class HealthLinkAutoCast;

	void applyHealthLink();
	
	volatile int healthLinkDamage;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* bubble;
	cocos2d::Sprite* spellAura;
	
	static const int MinHealthLink;
	static const int MaxMultiplier;
	static const float Duration;
};
