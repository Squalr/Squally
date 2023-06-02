#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class OverworldBoomerang : public Projectile
{
public:
	static OverworldBoomerang* create(PlatformerEntity* owner);

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	OverworldBoomerang(PlatformerEntity* owner);
	virtual ~OverworldBoomerang();

	void onEnter() override;

private:
	typedef Projectile super;

	PlatformerEntity* owner = nullptr;
	cocos2d::Sprite* boomerang = nullptr;
	
	WorldSound* boomerangSfx = nullptr;
	WorldSound* impactSfx = nullptr;
};
