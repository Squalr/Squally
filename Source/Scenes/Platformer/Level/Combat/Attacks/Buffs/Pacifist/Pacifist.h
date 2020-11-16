#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Pacifist : public Buff
{
public:
	static Pacifist* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string PacifistIdentifier;

protected:
	Pacifist(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Pacifist();

private:
	typedef Buff super;
};
