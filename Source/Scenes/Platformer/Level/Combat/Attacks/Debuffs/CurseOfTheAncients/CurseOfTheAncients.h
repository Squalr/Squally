#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class CurseOfTheAncients : public Buff
{
public:
	static CurseOfTheAncients* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CurseOfTheAncientsIdentifier;
	static const std::string HackIdentifierCurseOfTheAncients;

protected:
	CurseOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CurseOfTheAncients();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCurseOfTheAncients();
	
	SmartParticles* spellEffect;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
