#pragma once

#include "Objects/Platformer/Combat/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class SmartAnimationSequenceNode;

class ThrownWeapon : public Projectile
{
public:
	static ThrownWeapon* create(PlatformerEntity* caster, std::string weaponResource, int damage);

protected:
	ThrownWeapon(PlatformerEntity* caster, std::string weaponResource, int damage);
	virtual ~ThrownWeapon();

	void onEnter() override;
	void initializePositions() override;
	void onCollideWithTarget(PlatformerEntity* target) override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;

private:
	typedef Projectile super;

	int damage;
	std::string weaponResource;
	cocos2d::Sprite* weaponSprite;
	SmartAnimationSequenceNode* fire;
};
