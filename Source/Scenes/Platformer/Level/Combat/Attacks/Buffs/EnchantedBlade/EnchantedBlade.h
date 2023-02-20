#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class EnchantedBlade : public Buff
{
public:
	static EnchantedBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string EnchantedBladeIdentifier;
	static const std::string HackIdentifierEnchantedBlade;

protected:
	EnchantedBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~EnchantedBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyEnchantedBlade();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
