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
	static ThrownObject* create(PlatformerEntity* caster, std::string objectResource, cocos2d::Size collisionSize);
	static ThrownObject* create(PlatformerEntity* caster, cocos2d::Node* object, cocos2d::Size collisionSize);

	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);

protected:
	ThrownObject(PlatformerEntity* caster, cocos2d::Node* object, cocos2d::Size collisionSize);
	virtual ~ThrownObject();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;

private:
	typedef Projectile super;

	cocos2d::Node* cloneObject();
	
	cocos2d::Node* object;
};
