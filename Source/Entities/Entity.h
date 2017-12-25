#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	float GetWidth();
	float GetHeight();

protected:
	Entity();
	~Entity();

	void onEnter() override;
	void update(float) override;

	CollisionObject * collisionObject;
	Sprite * sprite;

	Vec2 movement;
	Vec2 velocity;

	bool isOnGround;

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	// STANDARD
	const float groundDragFactor = .58f;
	const float maxMoveSpeed = 360.0f;

	const float moveAcceleration = 14000.0f;
	const float airDragFactor = 0.65f;
	const float jumpLaunchVelocity = -4000.0f;
	const float gravityAcceleration = 1000.0f;
	const float maxFallSpeed = 600.0f;

	// UNDERWATER
	const float underwaterJumpLaunchVelocity = -3000.0f;
	const float underwaterGravityAcceleration = 250.0f;
	const float underwaterMaxFallSpeed = 200.0f;

	// GLIDE
	const float glideMaxFallSpeed = 150.0f;
};

