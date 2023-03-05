#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class PoisonedArrows : public Buff
{
public:
	static PoisonedArrows* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PoisonedArrowsIdentifier;
	static const int DamageAmount;
	static const int DamageAmountMax;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	PoisonedArrows(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~PoisonedArrows();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runPoisonedArrows();
	void runPoisonedArrowsTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount = 0;
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
