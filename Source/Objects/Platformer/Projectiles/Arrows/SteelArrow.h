#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class SteelArrow : public Projectile
{
public:
	static SteelArrow* create();

protected:
	SteelArrow();
	virtual ~SteelArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
