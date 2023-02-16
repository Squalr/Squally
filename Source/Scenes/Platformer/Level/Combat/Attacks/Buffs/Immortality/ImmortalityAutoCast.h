#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;

class ImmortalityAutoCast : public Buff
{
public:
	static ImmortalityAutoCast* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string ImmortalityAutoCastIdentifier;

protected:
	ImmortalityAutoCast(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ImmortalityAutoCast();

	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	bool hasAutoCasted = false;
};
