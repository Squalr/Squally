#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class SmartAnimationSequenceNode;
class WorldSound;

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
	SmartAnimationSequenceNode* shell = nullptr;
};
