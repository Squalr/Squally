#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Inversion : public Buff
{
public:
	static Inversion* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string InversionIdentifier;

protected:
	Inversion(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Inversion();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyInversion();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* bubble = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static volatile int currentDamageTaken;
	
	static const int MaxMultiplier;
	static const float Duration;
};
