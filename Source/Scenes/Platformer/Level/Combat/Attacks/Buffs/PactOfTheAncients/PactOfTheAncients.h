#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class PactOfTheAncients : public Buff
{
public:
	static PactOfTheAncients* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string PactOfTheAncientsIdentifier;

protected:
	PactOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~PactOfTheAncients();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyPactOfTheAncients();
	
	SmartParticles* spellEffect = nullptr;
	
	static volatile int healthLinkDamage;
	
	static const int MaxMultiplier;
	static const float Duration;
};
