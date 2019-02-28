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
	static ProjectileHealthPotion* create(std::function<void(PlatformerEntity* target)> onTargetHit);

protected:
	ProjectileHealthPotion(std::function<void(PlatformerEntity* target)> onTargetHit);
	virtual	~ProjectileHealthPotion();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;

private:
	typedef Projectile super;

	cocos2d::Sprite* healthPotionSprite;
};
