#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Melt : public Buff
{
public:
	static Melt* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string MeltIdentifier;
	static const std::string HackIdentifierMelt;

protected:
	Melt(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Melt();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyMelt();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int CritDamage;
	static const float Duration;
};
