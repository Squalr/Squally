#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Leech : public Buff
{
public:
	static Leech* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string LeechIdentifier;
	static const std::string HackIdentifierLeech;

protected:
	Leech(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Leech();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyLeech();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
