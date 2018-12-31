#pragma once
#include <set>

#include "cocos/math/CCGeometry.h"

#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

class SmartAnimationNode;
class SpeechBubble;

class PlatformerEntity : public CollisionObject
{
protected:
	PlatformerEntity(
		cocos2d::ValueMap* initProperties,
		std::string scmlResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size = cocos2d::Size(256.0f, 256.0f),
		float scale = 1.0f,
		cocos2d::Vec2 collisionOffset = cocos2d::Vec2(0.0f, 0.0f));
	~PlatformerEntity();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

	virtual void initializeCollisionEvents();

	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 spawnCoords;

	bool isOnGround();

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	float jumpLaunchVelocity;
	float gravityAcceleration;

	float moveAcceleration;

	static const float groundDragFactor;
	static const float airDragFactor;
	static const float maxMoveSpeed;
	static const float maxJumpSpeed;
	static const float maxFallSpeed;

private:
	typedef CollisionObject super;
	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale);

	std::set<CollisionObject*> groundCollisions;
	CollisionObject* groundCollisionDetector;

	static const float groundCollisionDetectorPadding;
	static const float groundCollisionDetectorOffset;
	static const float capsuleRadius;
};

