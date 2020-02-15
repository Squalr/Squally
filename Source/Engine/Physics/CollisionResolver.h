#pragma once
#include <functional>

#include "Engine/Physics/CollisionObject.h"
#include "Engine/SmartNode.h"

class CollisionObject;

class CollisionResolver
{
public:
	static void resolveCollision(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision);

private:
	typedef SmartNode super;

	static void quadToQuad(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision);
	static void quadToCircle(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision);
	static void circleToCircle(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision);
	static void polyToPoly(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision);
	static cocos2d::Vec2 applyCorrection(CollisionObject* objectA, CollisionObject* objectB, cocos2d::Vec2 correction, cocos2d::Vec2 impactNormal);
	static bool isWithinZThreshold(CollisionObject* collisionObjectA, CollisionObject* collisionObjectB);

	static void spawnDebugPoint(cocos2d::Vec2 point);
	static void spawnDebugVector(cocos2d::Vec2 pointA, cocos2d::Vec2 pointB, cocos2d::Color4F color);
};
