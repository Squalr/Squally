#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Regeneration : public Buff
{
public:
	static Regeneration* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string RegenerationIdentifier;
	static const float TimeBetweenTicks;
	static const int HealTicks;
	static const float StartDelay;

protected:
	Regeneration(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Regeneration();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runRegeneration();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;
};
