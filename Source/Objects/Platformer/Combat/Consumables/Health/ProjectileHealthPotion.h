#pragma once

#include "Objects/Platformer/Combat/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class SmartAnimationSequenceNode;

class ProjectileHealthPotion : public Projectile
{
public:
	static ProjectileHealthPotion* create(PlatformerEntity* caster);

protected:
	ProjectileHealthPotion(PlatformerEntity* caster);
	~ProjectileHealthPotion();

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

	cocos2d::Sprite* healthPotionSprite;

	static const float HealPercentage;
};
