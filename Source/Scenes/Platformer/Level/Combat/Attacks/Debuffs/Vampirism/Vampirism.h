#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Vampirism : public Buff
{
public:
	static Vampirism* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string VampirismIdentifier;
	static const std::string HackIdentifierVampirism;

protected:
	Vampirism(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Vampirism();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyVampirism();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReductionDivisor;
	static const float Duration;
};
