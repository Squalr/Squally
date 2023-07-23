#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class DefensiveStance : public Buff
{
public:
	static DefensiveStance* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string DefensiveStanceIdentifier;
	static const std::string HackIdentifierDefensiveStance;

protected:
	DefensiveStance(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~DefensiveStance();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyDefensiveStance();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
