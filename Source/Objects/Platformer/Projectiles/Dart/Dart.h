#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class Dart : public Projectile
{
public:
	static Dart* create(float dartRotation, float speed);

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	Dart(float dartRotation, float speed);
	virtual ~Dart();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
	float dartSpeed;
};
