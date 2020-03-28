#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;
class WorldSound;

class Bombed : public Buff
{
public:
	static Bombed* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string BombedIdentifier;

protected:
	Bombed(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Bombed();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef Buff super;
};
