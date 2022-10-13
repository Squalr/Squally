#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Rabies : public Buff
{
public:
	static Rabies* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string RabiesIdentifier;
	static const std::string HackIdentifierRabies;

protected:
	Rabies(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Rabies();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyRabies();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
