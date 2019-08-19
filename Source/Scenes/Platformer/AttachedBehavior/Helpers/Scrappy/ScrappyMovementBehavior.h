#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;

class ScrappyMovementBehavior : public AttachedBehavior
{
public:
	static ScrappyMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyMovementBehavior(GameObject* owner);
	~ScrappyMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Scrappy* scrappy;
	Squally* squally;

	float elapsed;
	float timeNearDest;

	static const float FloatOffsetRadius;
	static const float FloatOffsetAngle;
	static const cocos2d::Vec2 FlySpeedBase;
	static const float FlySpeedDistanceMultiplier;
};
