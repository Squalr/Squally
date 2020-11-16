#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class BoneArrow : public Projectile
{
public:
	static BoneArrow* create();

protected:
	BoneArrow();
	virtual ~BoneArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
