#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;

class Bombed : public Buff
{
public:
	static Bombed* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BombedIdentifier;

protected:
	Bombed(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Bombed();

private:
	typedef Buff super;
};
