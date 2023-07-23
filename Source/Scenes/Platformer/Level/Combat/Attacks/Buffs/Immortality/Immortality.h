#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Immortality : public Buff
{
public:
	static Immortality* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ImmortalityIdentifier;

protected:
	Immortality(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Immortality();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;
	friend class ImmortalityAutoCast;

	void applyImmortality();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* bubble = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const std::string StateKeyImmortalityNewHealth;
	static const int MinImmortality;
	static const int MaxMultiplier;
	static const float Duration;
};
