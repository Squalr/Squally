#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class Entity : public CollisionObject
{
public:
	float getWidth();
	float getHeight();

protected:
	Entity();
	~Entity();

	void onEnter() override;
	void update(float) override;

	Sprite * sprite;
	Vec2 movement;

	bool isOnGround;

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	float jumpLaunchVelocity;
	float gravityAcceleration;
	float maxFallSpeed;

	float moveAcceleration;

	const float groundDragFactor = .58f;
	const float airDragFactor = 0.65f;
	const float maxMoveSpeed = 360.0f;

	const float normalJumpThreshold = -0.8f;
};

