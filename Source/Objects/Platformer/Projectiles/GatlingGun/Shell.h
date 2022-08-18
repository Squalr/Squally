#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class WorldSound;

namespace cocos2d
{
	class Sprite;
}

class Shell : public Projectile
{
public:
	static Shell* create();

	void runSpawnFX() override;

protected:
	Shell();
	virtual ~Shell();

	void onEnter() override;

private:
	typedef Projectile super;

	WorldSound* shootSfx = nullptr;
	cocos2d::Sprite* shell = nullptr;
};
