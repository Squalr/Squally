#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;

class ManaLife : public Buff
{
public:
	static ManaLife* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string ManaLifeIdentifier;

protected:
	ManaLife(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ManaLife();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;

	virtual void onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing) override;
	virtual void onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing) override;
	virtual void onAfterHealingTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing) override;
	virtual void onAfterHealingDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyManaLife();
	
	static const float Duration;
};
