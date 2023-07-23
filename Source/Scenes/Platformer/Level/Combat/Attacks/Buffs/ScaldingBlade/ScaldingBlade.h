#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class ScaldingBlade : public Buff
{
public:
	static ScaldingBlade* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ScaldingBladeIdentifier;
	static const std::string HackIdentifierScaldingBlade;

protected:
	ScaldingBlade(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ScaldingBlade();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyScaldingBlade();
	
	cocos2d::Sprite* bubble = nullptr;
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const int MaxMultiplier;
	static const float Duration;
};
