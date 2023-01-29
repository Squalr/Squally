#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Manifest : public Buff
{
public:
	static Manifest* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string ManifestIdentifier;

protected:
	Manifest(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Manifest();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyManifest();
	
	static volatile int currentDamageDealt;
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MinMultiplier;
	static const int MaxMultiplier;
	static const int DamageIncrease;
	static const float Duration;
};
