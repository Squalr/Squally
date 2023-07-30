#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class AddHealth : public Buff
{
public:
	static AddHealth* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyAddHealthTutorial;
	static const std::string AddHealthIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	AddHealth(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~AddHealth();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runAddHealth();
	void runRestoreTick();

private:
	typedef Buff super;
	
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
