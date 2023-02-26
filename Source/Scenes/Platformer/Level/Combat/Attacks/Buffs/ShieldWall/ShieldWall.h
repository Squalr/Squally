#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class ShieldWall : public Buff
{
public:
	static ShieldWall* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ShieldWallIdentifier;
	static const std::string HackIdentifierShieldWall;

protected:
	ShieldWall(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ShieldWall();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyShieldWall();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
