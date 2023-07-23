#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Leech : public Buff
{
public:
	static Leech* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string LeechIdentifier;
	static const int TickCount;
	static const int DrainAmountMax;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	Leech(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Leech();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runLeech();
	void runLeechTick();

private:
	typedef Buff super;

	void incrementHeal();

	SmartAnimationSequenceNode* drainEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* drainSound = nullptr;
};
