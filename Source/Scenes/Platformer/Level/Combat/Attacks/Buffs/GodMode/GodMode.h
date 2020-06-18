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

class GodMode : public Buff
{
public:
	static GodMode* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string GodModeIdentifier;

protected:
	GodMode(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~GodMode();

	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;
};
