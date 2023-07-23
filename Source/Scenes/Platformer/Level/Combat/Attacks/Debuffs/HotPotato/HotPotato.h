#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class HotPotato : public Buff
{
public:
	static HotPotato* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string HotPotatoIdentifier;
	static const int HealAmount;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	HotPotato(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~HotPotato();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing) override;
	void runHotPotato();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount = 0;
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
