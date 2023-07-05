#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;
class SmartParticles;
class WorldSound;

class Condensation : public Buff
{
public:
	static Condensation* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CondensationIdentifier;
	static const float TimeBetweenTicks;
	static const int Ticks;
	static const float StartDelay;

protected:
	Condensation(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Condensation();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;

	SmartParticles* spellEffect = nullptr;
	SmartAnimationSequenceNode* restoreEffect = nullptr;
	WorldSound* restoreSound = nullptr;
};
