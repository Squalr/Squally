#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Condensation : public Buff
{
public:
	static Condensation* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CondensationIdentifier;

protected:
	Condensation(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Condensation();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;

	void applyCondensation();
	
	SmartParticles* spellEffect;
	
	static const float Duration;
};
