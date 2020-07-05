#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

class BrokenBlade : public Buff
{
public:
	static BrokenBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string BrokenBladeIdentifier;
	static const std::string HackIdentifierBrokenBlade;

protected:
	BrokenBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~BrokenBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyBrokenBlade();
	
	SmartParticles* spellEffect;
	
	static const int MaxMultiplier;
	static const float Duration;
};
