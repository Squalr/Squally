#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HuntersArrow : public Projectile
{
public:
	static HuntersArrow* create();

protected:
	HuntersArrow();
	virtual ~HuntersArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
