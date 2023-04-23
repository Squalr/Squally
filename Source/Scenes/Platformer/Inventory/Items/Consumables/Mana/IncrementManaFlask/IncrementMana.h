#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class IncrementMana : public Buff
{
public:
	static IncrementMana* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string PropertyIncrementManaTutorial;
	static const std::string IncrementManaIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	IncrementMana(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~IncrementMana();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runIncrementMana();
	void runRestoreTick();

private:
	typedef Buff super;
	
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
