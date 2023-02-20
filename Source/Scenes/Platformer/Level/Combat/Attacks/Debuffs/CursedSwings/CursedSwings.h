#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class CursedSwings : public Buff
{
public:
	static CursedSwings* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CursedSwingsIdentifier;

protected:
	CursedSwings(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CursedSwings();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCursedSwings();
	
	SmartParticles* spellEffect = nullptr;
	
	static volatile int cursedSwingsDamage;
	
	static const int MinCursedSwings;
	static const int MaxMultiplier;
	static const float Duration;
};
