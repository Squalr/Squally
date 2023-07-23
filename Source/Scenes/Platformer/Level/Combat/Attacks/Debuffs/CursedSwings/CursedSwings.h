#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class CursedSwings : public Buff
{
public:
	static CursedSwings* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string CursedSwingsIdentifier;
	static const std::string HackIdentifierCursedSwings;

protected:
	CursedSwings(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CursedSwings();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyCursedSwings();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const int MaxMultiplier;
};
