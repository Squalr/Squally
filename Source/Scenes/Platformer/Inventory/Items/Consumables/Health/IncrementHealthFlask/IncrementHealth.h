#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class IncrementHealth : public Buff
{
public:
	static IncrementHealth* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyIncrementHealthTutorial;
	static const std::string IncrementHealthIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	IncrementHealth(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~IncrementHealth();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runIncrementHealth();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;
};
