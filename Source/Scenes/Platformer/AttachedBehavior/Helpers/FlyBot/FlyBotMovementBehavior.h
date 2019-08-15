#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class FlyBot;
class Squally;

class FlyBotMovementBehavior : public AttachedBehavior
{
public:
	static FlyBotMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FlyBotMovementBehavior(GameObject* owner);
	~FlyBotMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	FlyBot* flyBot;
	Squally* squally;

	float elapsed;

	static const float FloatOffsetRadius;
	static const float FloatOffsetAngle;
	static const cocos2d::Vec2 FlySpeedBase;
	static const float FlySpeedDistanceMultiplier;
};
