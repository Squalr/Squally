#pragma once

#include "Objects/Platformer/Combat/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class SmartAnimationSequenceNode;

class ProjectileRestorePotion : public Projectile
{
public:
	static ProjectileRestorePotion* create();

protected:
	ProjectileRestorePotion();
	virtual	~ProjectileRestorePotion();

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

	cocos2d::Sprite* restorePotionSprite;

	static const float HealPercentage;
};
