#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Entwined : public Buff
{
public:
	static Entwined* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string EntwinedIdentifier;

protected:
	Entwined(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Entwined();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyEntwined();
	
	SmartParticles* spellEffect = nullptr;
	
	static volatile int healthLinkDamage;
	
	static const int MinEntwined;
	static const int MaxMultiplier;
	static const float Duration;
};
