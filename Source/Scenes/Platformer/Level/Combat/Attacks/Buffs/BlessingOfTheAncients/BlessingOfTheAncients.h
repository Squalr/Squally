#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class BlessingOfTheAncients : public Buff
{
public:
	static BlessingOfTheAncients* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BlessingOfTheAncientsIdentifier;

protected:
	BlessingOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~BlessingOfTheAncients();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyBlessingOfTheAncients();
	
	static volatile int currentDamageDealt;
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MinMultiplier;
	static const int MaxMultiplier;
	static const int DamageIncrease;
	static const float Duration;
};
