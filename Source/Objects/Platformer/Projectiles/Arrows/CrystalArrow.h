#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class CrystalArrow : public Projectile
{
public:
	static CrystalArrow* create();

protected:
	CrystalArrow();
	virtual ~CrystalArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
