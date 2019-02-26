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
	Projectile(std::function<void(PlatformerEntity* target)> onTargetHit, float radius, float noCollideDuration);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

private:
	typedef ProximityObject super;

	std::function<void(PlatformerEntity* target)> onTargetHit;
	bool hasCollided;
	float noCollideDuration;
	float elapsedDuration;
};
