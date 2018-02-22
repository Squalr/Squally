#pragma once
#include <algorithm>
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class Entity : public CollisionObject
{
public:
	virtual Size getSize();

protected:
	Entity();
	~Entity();

	void onEnter() override;
	void update(float) override;

	Node * spriteNode;
	Vec2 movement;

	bool isOnGround;

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	float jumpLaunchVelocity;
	float gravityAcceleration;

	float moveAcceleration;

	const float groundDragFactor = .58f;
	const float airDragFactor = 0.65f;
	const float maxMoveSpeed = 360.0f;
	const float maxFallSpeed = 360.0f;

	const float normalJumpThreshold = 0.8f;
};

