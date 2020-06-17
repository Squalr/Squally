#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

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
