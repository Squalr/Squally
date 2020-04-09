#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class GoldenArrow : public Projectile
{
public:
	static GoldenArrow* create();

protected:
	GoldenArrow();
	virtual ~GoldenArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
