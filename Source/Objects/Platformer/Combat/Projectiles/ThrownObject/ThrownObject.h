#pragma once

#include "Objects/Platformer/Combat/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;

class ThrownObject : public Projectile
{
public:
	static ThrownObject* create(PlatformerEntity* caster, std::string objectResource);

protected:
	ThrownObject(PlatformerEntity* caster, std::string objectResource);
	virtual ~ThrownObject();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;

private:
	typedef Projectile super;

	std::string objectResource;
	cocos2d::Sprite* objectSprite;
};
