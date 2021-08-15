#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Undying : public Buff
{
public:
	static Undying* create(PlatformerEntity* caster, PlatformerEntity* target);
	
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
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* bubble = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const std::string StateKeyUndyingHealth;
	static const int MinUndying;
	static const int MaxMultiplier;
	static const float Duration;
};
