#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Chance : public Buff
{
public:
	static Chance* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ChanceIdentifier;
	static const std::string HackIdentifierChance;

protected:
	Chance(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Chance();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyChance();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const float Duration;
};
