#pragma once

#include "Objects/Platformer/Combat/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class BomberTorch : public Projectile
{
public:
	static BomberTorch* create(PlatformerAttack* associatedAttack);

protected:
	BomberTorch(PlatformerAttack* associatedAttack);
	virtual	~BomberTorch();

private:
	typedef Projectile super;

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

	cocos2d::Sprite* bomberTorchSprite;
};
