#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Rejuvination : public Buff
{
public:
	static Rejuvination* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string RejuvinationIdentifier;
	static const float TimeBetweenTicks;
	static const int HealTicks;
	static const int MaxHealing;
	static const float StartDelay;

protected:
	Rejuvination(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Rejuvination();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runRejuvination();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
