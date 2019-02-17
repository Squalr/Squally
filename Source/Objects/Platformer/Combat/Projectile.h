#pragma once

#include "Engine/Physics/ProximityObject.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerAttack;

class Projectile : public ProximityObject
{
protected:
	Projectile(PlatformerAttack* associatedAttack, float radius, float noCollideDuration);
	virtual	~Projectile();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

private:
	typedef ProximityObject super;

	PlatformerAttack* associatedAttack;
	bool hasCollided;
	float noCollideDuration;
	float elapsedDuration;
};
