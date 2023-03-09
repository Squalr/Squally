#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Cauterize : public Buff
{
public:
	static Cauterize* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CauterizeIdentifier;
	static const float TimeBetweenTicks;
	static const int HealTicks;
	static const float StartDelay;
	static const int MaxHealing;

protected:
	Cauterize(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Cauterize();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runCauterize();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
