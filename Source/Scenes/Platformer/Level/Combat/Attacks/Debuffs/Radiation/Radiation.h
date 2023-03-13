#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Radiation : public Buff
{
public:
	static Radiation* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string RadiationIdentifier;
	static const int DamageAmount;
	static const int DamageAmountMax;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	Radiation(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Radiation();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runRadiation();
	void runRadiationTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount = 0;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
