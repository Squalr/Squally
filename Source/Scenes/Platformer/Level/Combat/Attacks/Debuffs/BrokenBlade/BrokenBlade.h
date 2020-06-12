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

	static const std::string PropertyRestorePotionTutorial;
	static const std::string BrokenBladeIdentifier;
	static const std::string HackIdentifierBrokenBlade;

protected:
	BrokenBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~BrokenBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDelt(ModifyableDamageOrHealing damageOrHealing) override;

private:
	typedef Buff super;

	void applyBrokenBlade();
	
	volatile int currentDamageDelt;
	
	cocos2d::Sprite* bubble;
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;
	
	static const int MaxMultiplier;
	static const int DamageReduction;
	static const float Duration;
};
