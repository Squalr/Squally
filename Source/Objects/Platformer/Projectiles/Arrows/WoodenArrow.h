#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class WoodenArrow : public Projectile
{
public:
	static WoodenArrow* create();

protected:
	WoodenArrow();
	virtual ~WoodenArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
