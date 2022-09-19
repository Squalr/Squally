#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class BrittleBones : public Buff
{
public:
	static BrittleBones* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string BrittleBonesIdentifier;
	static const std::string HackIdentifierBrittleBones;

protected:
	BrittleBones(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~BrittleBones();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyBrittleBones();
	
	SmartParticles* spellEffect = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageDelt;
	static const float Duration;
};
