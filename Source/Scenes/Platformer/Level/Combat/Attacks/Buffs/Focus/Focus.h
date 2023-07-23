#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Focus : public Buff
{
public:
	static Focus* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string FocusIdentifier;
	static const std::string HackIdentifierFocus;

protected:
	Focus(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Focus();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyFocus();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const float DamageIncrease;
	static const int MaxMultiplier;
};
