#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Bloodletting : public Buff
{
public:
	static Bloodletting* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BloodlettingIdentifier;
	static const int DamageAmount;
	static const int DamageAmountMax;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	Bloodletting(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Bloodletting();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runBloodletting();
	void runBloodlettingTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount = 0;
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
