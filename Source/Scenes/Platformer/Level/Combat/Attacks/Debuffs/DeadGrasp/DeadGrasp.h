#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class DeadGrasp : public Buff
{
public:
	static DeadGrasp* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string DeadGraspIdentifier;
	static const std::string HackIdentifierDeadGrasp;

protected:
	DeadGrasp(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~DeadGrasp();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyDeadGrasp();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const float DamageIncrease;
	static const int MaxMultiplier;
};
