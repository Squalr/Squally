#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class DemonicArrow : public Projectile
{
public:
	static DemonicArrow* create();

protected:
	DemonicArrow();
	virtual ~DemonicArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* sprite;
};
