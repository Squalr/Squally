#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Blind : public Buff
{
public:
	static Blind* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BlindIdentifier;

protected:
	Blind(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Blind();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyBlind();
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const float Duration;
	static const int DamageDealt;
};
