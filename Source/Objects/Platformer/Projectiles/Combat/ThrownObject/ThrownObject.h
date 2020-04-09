#pragma once

#include "Objects/Platformer/Projectiles/Combat/CombatProjectile.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;

class ThrownObject : public CombatProjectile
{
public:
	static ThrownObject* create(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, std::string objectResource, cocos2d::Size collisionSize);
	static ThrownObject* create(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, cocos2d::Node* object, cocos2d::Size collisionSize);

	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);

protected:
	ThrownObject(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, cocos2d::Node* object, cocos2d::Size collisionSize);
	virtual ~ThrownObject();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;
	
	cocos2d::Node* object;

private:
	typedef CombatProjectile super;

	cocos2d::Node* cloneObject();
};
