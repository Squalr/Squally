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

class Undying : public Buff
{
public:
	static Undying* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyRestorePotionTutorial;
	static const std::string UndyingIdentifier;

protected:
	Undying(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Undying();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;
	friend class UndyingAutoCast;

	void applyUndying();
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* bubble;
	cocos2d::Sprite* spellAura;
	
	static const std::string StateKeyUndyingHealth;
	static const int MinUndying;
	static const int MaxMultiplier;
	static const float Duration;
};
