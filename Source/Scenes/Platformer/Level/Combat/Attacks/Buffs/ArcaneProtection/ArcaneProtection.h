#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class ArcaneProtection : public Buff
{
public:
	static ArcaneProtection* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ArcaneProtectionIdentifier;
	static const std::string HackIdentifierArcaneProtection;

protected:
	ArcaneProtection(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ArcaneProtection();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyArcaneProtection();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
