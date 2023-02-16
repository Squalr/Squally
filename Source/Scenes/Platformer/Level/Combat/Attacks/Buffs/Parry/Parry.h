#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Parry : public Buff
{
public:
	static Parry* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ParryIdentifier;

protected:
	Parry(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Parry();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyParry();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* bubble = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const std::string StateKeyDamageParryed;

	static const int MinMultiplier;
	static const int MaxMultiplier;
	static const float Duration;
};
