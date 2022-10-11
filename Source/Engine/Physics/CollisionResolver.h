#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

class CollisionObject;

enum class CollisionResult;

class CollisionResolver
{
public:
	static void resolveCollision(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);

	static void spawnDebugPoint(CollisionObject* objectA, cocos2d::Vec2 point, cocos2d::Color4F color);
	static void spawnDebugVector(CollisionObject* objectA, cocos2d::Vec2 pointA, cocos2d::Vec2 pointB, cocos2d::Color4F color);
	static void spawnDebugShapes(CollisionObject* objectA);

private:
	static void rectToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static void rectToRect(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static void quadToQuad(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static void polyToPoly(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static void polyToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static void segmentToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionResult()> onCollision);
	static cocos2d::Vec2 applyCorrection(CollisionObject* objectA, CollisionObject* objectB, cocos2d::Vec2 correction, cocos2d::Vec2 impactNormal);
	static bool isWithinZThreshold(CollisionObject* collisionObjectA, CollisionObject* collisionObjectB);
	static bool isQuadCompatible(CollisionObject* objectA);
	static bool isPolyCompatible(CollisionObject* objectA);
};
