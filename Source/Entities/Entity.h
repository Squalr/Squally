#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/Collision.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	float getWidth();
	float getHeight();

protected:
	Entity();
	~Entity();

	void onEnter() override;
	void update(float) override;
	void initializeListeners();
	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	Sprite * sprite;

	Vec2 movement;

	PhysicsBody * physicsBody;
	Collision::CollisionGroup collisionGroup;

	bool isOnGround;

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	// STANDARD
	const float groundDragFactor = .58f;
	const float airDragFactor = 0.65f;

	const float maxMoveSpeed = 360.0f;
	const float moveAcceleration = 14000.0f;

	const float jumpLaunchVelocity = 640.0f;
	const float gravityAcceleration = 1000.0f;
	const float maxFallSpeed = 600.0f;

	// UNDERWATER
	const float underwaterJumpLaunchVelocity = 128.0f;
	const float underwaterGravityAcceleration = 250.0f;
	const float underwaterMaxFallSpeed = 200.0f;

	// GLIDE
	const float glideMaxFallSpeed = 150.0f;
};

