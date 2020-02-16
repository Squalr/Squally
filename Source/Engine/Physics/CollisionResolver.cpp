#include "CollisionResolver.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/SmartNode.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

void CollisionResolver::resolveCollision(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	// Check for easy disqualifications
	if (objectA == nullptr
		|| objectB == nullptr
		|| objectA == objectB
		|| !objectA->physicsEnabled
		|| !objectB->physicsEnabled
		|| !CollisionResolver::isWithinZThreshold(objectA, objectB))
	{
		return;
	}

	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);
	
	Rect thisRect = objectA->boundsRect;
	Rect otherRect = objectB->boundsRect;

	thisRect.origin += coordsA;
	otherRect.origin += coordsB;

	// Cheap and easy bounds check
	if (!thisRect.intersectsRect(otherRect))
	{
		return;
	}

	if (objectA->shape.size() == 4 && objectB->shape.size() == 4)
	{
		CollisionResolver::quadToQuad(objectA, objectB, onCollision);
	}
	else if (objectA->shape.size() == 2 && objectB->shape.size() > 2)
	{
		CollisionResolver::polyToSegment(objectB, objectA, onCollision);
	}
	else if (objectA->shape.size() > 2 && objectB->shape.size() == 2)
	{
		CollisionResolver::polyToSegment(objectA, objectB, onCollision);
	}
	else if (objectA->shape.size() == 0 && objectB->shape.size() == 0)
	{
		CollisionResolver::circleToCircle(objectA, objectB, onCollision);
	}
	else if ((objectA->shape.size() == 0 || objectB->shape.size() == 0) && (objectA->shape.size() == 4 || objectB->shape.size() == 4))
	{
		CollisionResolver::quadToCircle(objectA, objectB, onCollision);
	}
	else
	{
		CollisionResolver::polyToPoly(objectA, objectB, onCollision);
	}
}

bool CollisionResolver::isWithinZThreshold(CollisionObject* collisionObjectA, CollisionObject* collisionObjectB)
{
	const float thisDepth = GameUtils::getDepth(collisionObjectA);
	const float otherDepth = GameUtils::getDepth(collisionObjectB);

	if (std::abs(thisDepth - otherDepth) >= CollisionObject::CollisionZThreshold)
	{
		return false;
	}

	return true;
}

void CollisionResolver::quadToQuad(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	auto resolve = [](CollisionObject* innerObject, CollisionObject* outerObject, std::vector<cocos2d::Vec2>& outerShape, Vec2 innerPoint)
	{
		std::tuple<Vec2, Vec2> ab = std::make_tuple(outerShape[0], outerShape[1]);
		std::tuple<Vec2, Vec2> bc = std::make_tuple(outerShape[1], outerShape[2]);
		std::tuple<Vec2, Vec2> cd = std::make_tuple(outerShape[2], outerShape[3]);
		std::tuple<Vec2, Vec2> da = std::make_tuple(outerShape[3], outerShape[0]);

		float abDist = AlgoUtils::getDistanceFromSegment(ab, innerPoint);
		float bcDist = AlgoUtils::getDistanceFromSegment(bc, innerPoint);
		float cdDist = AlgoUtils::getDistanceFromSegment(cd, innerPoint);
		float daDist = AlgoUtils::getDistanceFromSegment(da, innerPoint);

		Vec2 closestPoint;
		Vec2 normal;

		if ((abDist < bcDist) && (abDist < cdDist) && (abDist < daDist))
		{
			closestPoint = AlgoUtils::getClosestPointOnLine(ab, innerPoint);
			normal = AlgoUtils::getSegmentNormal(ab);
		}
		else if ((bcDist < cdDist) && (bcDist < daDist))
		{
			closestPoint = AlgoUtils::getClosestPointOnLine(bc, innerPoint);
			normal = AlgoUtils::getSegmentNormal(bc);
		}
		else if (cdDist < daDist)
		{
			closestPoint = AlgoUtils::getClosestPointOnLine(cd, innerPoint);
			normal = AlgoUtils::getSegmentNormal(cd);
		}
		else
		{
			closestPoint = AlgoUtils::getClosestPointOnLine(da, innerPoint);
			normal = AlgoUtils::getSegmentNormal(da);
		}

		CollisionResolver::applyCorrection(innerObject, outerObject, closestPoint - innerPoint, normal);
	};

	bool hasRunEvents = false;
	CollisionObject::CollisionResult result = CollisionObject::CollisionResult::DoNothing;

	auto runCollisonEventsOnce = [&]()
	{
		if (!hasRunEvents)
		{
			hasRunEvents = true;
			result = onCollision();
		}

		return result;
	};

	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);

	std::vector<cocos2d::Vec2> shapeA = objectA->shape;
	std::vector<cocos2d::Vec2> shapeB = objectB->shape;

	for (cocos2d::Vec2& point : shapeA)
	{
		point += coordsA;
	}

	for (cocos2d::Vec2& point : shapeB)
	{
		point += coordsB;
	}

	for (auto point : shapeA)
	{
		if (AlgoUtils::isPointInPolygon(shapeB, point))
		{
			if (runCollisonEventsOnce() == CollisionObject::CollisionResult::CollideWithPhysics)
			{
				resolve(objectA, objectB, shapeB, point);
			}
		}
	}

	for (auto point : shapeB)
	{
		if (AlgoUtils::isPointInPolygon(shapeA, point))
		{
			if (runCollisonEventsOnce() == CollisionObject::CollisionResult::CollideWithPhysics)
			{
				resolve(objectB, objectA, shapeA,  point);
			}
		}
	}
}

void CollisionResolver::quadToCircle(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{

}

void CollisionResolver::circleToCircle(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{

}

void CollisionResolver::polyToPoly(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);

	CollisionObject::CollisionResult collisionResult = CollisionObject::CollisionResult::DoNothing;

	if (std::any_of(objectA->shape.begin(), objectA->shape.end(), [=](Vec2 point)
		{
			point += (coordsA - coordsB);

			return AlgoUtils::isPointInPolygon(objectB->shape, point);
		})
		|| std::any_of(objectB->shape.begin(), objectB->shape.end(), [=](Vec2 point)
		{
			point += (coordsB - coordsA);
			
			return AlgoUtils::isPointInPolygon(objectA->shape, point);
		}))
	{
		collisionResult = onCollision();
	}

	if (collisionResult != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	// TODO: Resolve
}

void CollisionResolver::polyToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);

	std::tuple<Vec2, Vec2> currentSegment;
	std::tuple<Vec2, Vec2> otherSegment = std::make_tuple(coordsB + std::get<0>(objectB->segments[0]), coordsB + std::get<1>(objectB->segments[0]));
	bool hadCollision = false;

	for (auto currentSegment : objectA->segments)
	{
		currentSegment = std::make_tuple(coordsA + std::get<0>(currentSegment), coordsA + std::get<1>(currentSegment));

		if (AlgoUtils::doSegmentsIntersect(currentSegment, otherSegment))
		{
			if (!hadCollision)
			{
				if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
				{
					return;
				}

				hadCollision = true;
			}

			Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(currentSegment, otherSegment);
			float thisDistanceA = std::get<0>(currentSegment).distance(intersectionPoint);
			float thisDistanceB = std::get<1>(currentSegment).distance(intersectionPoint);
			float otherDistanceA = std::get<0>(otherSegment).distance(intersectionPoint);
			float otherDistanceB = std::get<1>(otherSegment).distance(intersectionPoint);

			Vec2 correction = Vec2::ZERO;
			Vec2 normal = Vec2::ZERO;

			// CollisionResolver::spawnDebugPoint(objectA, intersectionPoint);

			if (std::min(thisDistanceA, thisDistanceB) < std::min(otherDistanceA, otherDistanceB))
			{
				// Case 1: The end of this segment is close to the intersection point. Snap the end of this segment to intersect the other segment.
				normal = AlgoUtils::getSegmentNormal(otherSegment);

				// CollisionResolver::spawnDebugVector(objectA, std::get<0>(currentSegment), std::get<1>(currentSegment), Color4F::GREEN);

				if (thisDistanceA < thisDistanceB)
				{
					correction = intersectionPoint - std::get<0>(currentSegment);
				}
				else
				{
					correction = intersectionPoint - std::get<1>(currentSegment);
				}
			}
			else
			{
				// Case 2: The end of the other segment is closer to the intersection point. The other object can't snap since it's static,
				// so instead we need to push this object away by a calculated amount
				normal = AlgoUtils::getSegmentNormal(currentSegment);

				// CollisionResolver::spawnDebugVector(objectA, std::get<0>(otherSegment), std::get<1>(otherSegment), Color4F::BLUE);

				if (otherDistanceA < otherDistanceB)
				{
					correction = std::get<0>(otherSegment) - intersectionPoint;
				}
				else
				{
					correction = std::get<1>(otherSegment) - intersectionPoint;
				}
			}

			coordsA += CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
		}
	}
}

void CollisionResolver::segmentToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	
}

Vec2 CollisionResolver::applyCorrection(CollisionObject* objectA, CollisionObject* objectB, Vec2 correction, Vec2 impactNormal)
{
	correction.x *= impactNormal.x;
	correction.y *= impactNormal.y;
	
	// If disabled, this makes for better horizontal movement, but enabled is more realistic. Might need a compromise/toggleability
	// objectA->velocity.x *= impactNormal.y;
	objectA->velocity.y *= impactNormal.x;

	if (objectA->isDynamic && objectB->isDynamic)
	{
		// TODO: Instead of weighting each object equally, allow for this to be configurable (ie 75% of force to one object, 25% to other).
		// Unsure of best implementation for this.
		correction.x /= 2.0f;
		correction.y /= 2.0f;
		
		// Equal and opposite force on other dynamic objects
		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + correction);
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() - correction);
	}
	else if (objectA->isDynamic)
	{
		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + correction);
	}
	else if (objectB->isDynamic)
	{
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() + correction);
	}

	return correction;
}

void CollisionResolver::spawnDebugPoint(CollisionObject* objectA, Vec2 point, Color4F color)
{
	DrawNode* dbg = DrawNode::create();

	dbg->drawPoint(point, 4.0f, color);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		objectA,
		dbg,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));
}

void CollisionResolver::spawnDebugVector(CollisionObject* objectA, Vec2 pointA, Vec2 pointB, Color4F color)
{
	DrawNode* dbg = DrawNode::create();

	dbg->drawSegment(pointA, pointB, 1.0f, color);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		objectA,
		dbg,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));
}
