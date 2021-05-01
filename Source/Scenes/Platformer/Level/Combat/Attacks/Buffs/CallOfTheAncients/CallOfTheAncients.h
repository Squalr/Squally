#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class CallOfTheAncients : public Buff
{
public:
	static CallOfTheAncients* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string CallOfTheAncientsIdentifier;

protected:
	CallOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CallOfTheAncients();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCallOfTheAncients();
	
	static volatile int currentDamageDealt;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const float Duration;
};
