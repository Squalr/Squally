#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Diseased : public Buff
{
public:
	static Diseased* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string DiseasedIdentifier;
	static const std::string HackIdentifierDiseased;

protected:
	Diseased(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Diseased();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyDiseased();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
