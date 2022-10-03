#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Fear : public Buff
{
public:
	static Fear* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string FearIdentifier;
	static const std::string HackIdentifierFear;

protected:
	Fear(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Fear();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyFear();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const float Duration;
};
