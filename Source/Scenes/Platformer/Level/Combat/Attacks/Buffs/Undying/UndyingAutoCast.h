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

class UndyingAutoCast : public Buff
{
public:
	static UndyingAutoCast* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string UndyingAutoCastIdentifier;

protected:
	UndyingAutoCast(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~UndyingAutoCast();

	void onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing) override;

private:
	typedef Buff super;

	bool hasAutoCasted;
};
