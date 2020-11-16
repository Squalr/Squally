#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class VoidArrow : public Projectile
{
public:
	static VoidArrow* create();

protected:
	VoidArrow();
	virtual ~VoidArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
