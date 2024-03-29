#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class SmartAnimationSequenceNode;
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
	void runImpactFX(bool isCrit);

protected:
	Shell();
	virtual ~Shell();

	void onEnter() override;

private:
	typedef Projectile super;

	WorldSound* shootSfx = nullptr;
	WorldSound* hitSfx = nullptr;
	WorldSound* critSfx = nullptr;
	cocos2d::Sprite* shell = nullptr;
	SmartAnimationSequenceNode* damageFx = nullptr;
};
