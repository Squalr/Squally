#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class InnerFire : public Buff
{
public:
	static InnerFire* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string InnerFireIdentifier;
	static const float TimeBetweenTicks;
	static const int HealTicks;
	static const float StartDelay;
	static const int MaxHealing;

protected:
	InnerFire(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~InnerFire();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runInnerFire();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
