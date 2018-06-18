#pragma once
#include "cocos2d.h"

#include "Objects/Hackables/HackableObject.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Utils/MathUtils.h"

using namespace cocos2d;

class Entity : public HackableObject
{
public:
	virtual Size getSize();

protected:
	Entity(
		std::string scmlResource,
		bool isFlying,
		Size size = Size(256.0f, 256.0f),
		float scale = 1.0f,
		Vec2 collisionOffset = Vec2(0.0f, 0.0f));
	~Entity();

	void onEnter() override;
	void update(float) override;

	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

	AnimationNode* animationNode;
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

