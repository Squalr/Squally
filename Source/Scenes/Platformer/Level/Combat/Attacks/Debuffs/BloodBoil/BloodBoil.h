#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class BloodBoil : public Buff
{
public:
	static BloodBoil* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BloodBoilIdentifier;
	static const std::string HackIdentifierBloodBoil;

protected:
	BloodBoil(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~BloodBoil();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyBloodBoil();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const int MaxMultiplier;
};
