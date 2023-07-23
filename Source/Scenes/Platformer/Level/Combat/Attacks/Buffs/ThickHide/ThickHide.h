#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class ThickHide : public Buff
{
public:
	static ThickHide* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ThickHideIdentifier;
	static const std::string HackIdentifierThickHide;

protected:
	ThickHide(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ThickHide();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyThickHide();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
