#pragma once

#include "Objects/Platformer/Combat/Projectiles/CombatProjectile.h"

class HackablePreview;

class ThrownObject : public CombatProjectile
{
public:
	static ThrownObject* create(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, std::string objectResource, cocos2d::CSize collisionSize);
	static ThrownObject* create(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, cocos2d::Node* object, cocos2d::CSize collisionSize);

	bool canCollide();

	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);

protected:
	ThrownObject(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, cocos2d::Node* object, cocos2d::CSize collisionSize);
	virtual ~ThrownObject();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	HackablePreview* createVelocityPreview() override;
	HackablePreview* createAccelerationPreview() override;
	
	cocos2d::Node* object = nullptr;

private:
	typedef CombatProjectile super;

	cocos2d::Node* cloneObject();

	float noCollideDuration = 1.0f;
};
