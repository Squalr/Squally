#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class Squally;

class ScrappyMovementBehavior : public AttachedBehavior
{
public:
	static ScrappyMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyMovementBehavior(GameObject* owner);
	virtual ~ScrappyMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Scrappy* scrappy;
	Squally* squally;

	float elapsed;
	float timeNearDestX;
	float timeNearDestY;

	static const float FloatOffsetRadius;
	static const float FloatOffsetAngle;
	static const cocos2d::Vec2 FlySpeedBase;
	static const float FlySpeedDistanceMultiplier;
};
