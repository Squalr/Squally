#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class CursedBlade : public Buff
{
public:
	static CursedBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CursedBladeIdentifier;
	static const std::string HackIdentifierCursedBlade;

protected:
	CursedBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CursedBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCursedBlade();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
