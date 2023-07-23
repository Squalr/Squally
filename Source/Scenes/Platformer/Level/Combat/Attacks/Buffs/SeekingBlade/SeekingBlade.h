#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class SeekingBlade : public Buff
{
public:
	static SeekingBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string SeekingBladeIdentifier;
	static const std::string HackIdentifierSeekingBlade;

protected:
	SeekingBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SeekingBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applySeekingBlade();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int CritDamage;
	static const float Duration;
};
