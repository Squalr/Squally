#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class UnholyProtection : public Buff
{
public:
	static UnholyProtection* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	
	static const std::string UnholyProtectionIdentifier;
	static const std::string HackIdentifierUnholyProtection;

protected:
	UnholyProtection(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~UnholyProtection();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;

private:
	typedef Buff super;

	void applyUnholyProtection();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;

	static const std::string StateKeyUnholyProtectionNewHealth;
	static const int MinUnholyProtection;
	static const int MaxMultiplier;
	static const float Duration;
};
