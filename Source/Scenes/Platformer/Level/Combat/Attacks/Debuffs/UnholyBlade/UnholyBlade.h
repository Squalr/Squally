#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class UnholyBlade : public Buff
{
public:
	static UnholyBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string UnholyBladeIdentifier;
	static const std::string HackIdentifierUnholyBlade;

protected:
	UnholyBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~UnholyBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyUnholyBlade();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
