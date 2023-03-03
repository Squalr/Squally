#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Daze : public Buff
{
public:
	static Daze* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string DazeIdentifier;
	static const std::string HackIdentifierDaze;

protected:
	Daze(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Daze();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyDaze();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const float DazeDamage;
	static const int MaxMultiplier;
};
