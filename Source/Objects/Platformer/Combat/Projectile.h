#pragma once

#include "Engine/Physics/ProximityObject.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class Projectile : public ProximityObject
{
protected:
	Projectile(PlatformerEntity* caster, float radius, float noCollideDuration, bool allowHacking);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	virtual void onCollideWithTarget(PlatformerEntity* target) = 0;
	
	PlatformerEntity* caster;

private:
	typedef ProximityObject super;

	bool hasCollided;
	float noCollideDuration;
	float elapsedDuration;
};
