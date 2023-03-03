#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Enchantment : public Buff
{
public:
	static Enchantment* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string EnchantmentIdentifier;
	static const std::string HackIdentifierEnchantment;

protected:
	Enchantment(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Enchantment();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyEnchantment();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const float DamageIncrease;
	static const int MaxMultiplier;
};
