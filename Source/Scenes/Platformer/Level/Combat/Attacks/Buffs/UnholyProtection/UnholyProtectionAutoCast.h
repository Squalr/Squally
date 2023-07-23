#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;

class UnholyProtectionAutoCast : public Buff
{
public:
	static UnholyProtectionAutoCast* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string UnholyProtectionAutoCastIdentifier;

protected:
	UnholyProtectionAutoCast(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~UnholyProtectionAutoCast();

	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	bool hasAutoCasted = false;
};
