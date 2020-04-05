#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class BombedClippy;
class SmartParticles;
class WorldSound;

class Bombed : public Buff
{
public:
	static Bombed* create(PlatformerEntity* caster, PlatformerEntity* target);

protected:
	Bombed(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Bombed();

private:
	typedef Buff super;
};
