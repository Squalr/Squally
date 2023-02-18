#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Hex : public Buff
{
public:
	static Hex* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string HexIdentifier;

protected:
	Hex(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Hex();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyHex();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const int MaxMultiplier;
};
