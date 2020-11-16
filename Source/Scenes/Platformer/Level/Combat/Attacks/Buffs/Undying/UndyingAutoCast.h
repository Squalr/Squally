#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;

class UndyingAutoCast : public Buff
{
public:
	static UndyingAutoCast* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string UndyingAutoCastIdentifier;

protected:
	UndyingAutoCast(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~UndyingAutoCast();

	void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;
	void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	bool hasAutoCasted;
};
