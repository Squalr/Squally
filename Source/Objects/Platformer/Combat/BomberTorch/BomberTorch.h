#pragma once

#include "Objects/Platformer/Combat/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class SmartAnimationSequenceNode;

class BomberTorch : public Projectile
{
public:
	static BomberTorch* create(PlatformerEntity* caster, int damage);

protected:
	BomberTorch(PlatformerEntity* caster, int damage);
	~BomberTorch();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void onCollideWithTarget(PlatformerEntity* target) override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;

private:
	typedef Projectile super;

	int damage;
	cocos2d::Sprite* bomberTorchSprite;
	SmartAnimationSequenceNode* fire;
};
