#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class IvyArrow : public Projectile
{
public:
	static IvyArrow* create();

protected:
	IvyArrow();
	virtual ~IvyArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
