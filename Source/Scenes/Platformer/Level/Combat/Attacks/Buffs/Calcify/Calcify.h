#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Calcify : public Buff
{
public:
	static Calcify* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CalcifyIdentifier;
	static const std::string HackIdentifierCalcify;

protected:
	Calcify(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Calcify();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCalcify();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
