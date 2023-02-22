#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Enflame : public Buff
{
public:
	static Enflame* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string EnflameIdentifier;
	static const int DamageAmount;
	static const int DamageAmountMax;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	Enflame(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Enflame();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runEnflame();
	void runEnflameTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount = 0;
	SmartAnimationSequenceNode* healEffect = nullptr;
	WorldSound* impactSound = nullptr;
	WorldSound* healSound = nullptr;
};
