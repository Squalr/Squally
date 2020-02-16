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

	if (objectA->shape == CollisionObject::Shape::Rectangle && objectB->shape == CollisionObject::Shape::Rectangle)
	{
		CollisionResolver::rectToRect(objectA, objectB, onCollision);
	}
	else if (CollisionResolver::isQuadCompatible(objectA) && CollisionResolver::isQuadCompatible(objectB))
	{
		CollisionResolver::quadToQuad(objectA, objectB, onCollision);
	}
	else if (objectA->shape == CollisionObject::Shape::Segment && objectB->shape == CollisionObject::Shape::Segment)
	{
		CollisionResolver::segmentToSegment(objectA, objectB, onCollision);
	}
	else if (objectA->shape == CollisionObject::Shape::Segment && CollisionResolver::isPolyCompatible(objectB))
	{
		CollisionResolver::polyToSegment(objectB, objectA, onCollision);
	}
	else if (CollisionResolver::isPolyCompatible(objectA) && objectB->shape == CollisionObject::Shape::Segment)
	{
		CollisionResolver::polyToSegment(objectA, objectB, onCollision);
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

void CollisionResolver::rectToRect(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
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

	if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	Vec2 correction = thisRect.size - otherRect.size;
	Vec2 normal = correction.getNormalized();

	normal.x = std::abs(normal.x);
	normal.y = std::abs(normal.y);

	CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
}

void CollisionResolver::quadToQuad(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
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

	auto resolve = [](CollisionObject* innerObject, CollisionObject* outerObject, Vec2 innerPoint)
	{
		std::tuple<Vec2, Vec2> ab = std::make_tuple(outerObject->points[0], outerObject->points[1]);
		std::tuple<Vec2, Vec2> bc = std::make_tuple(outerObject->points[1], outerObject->points[2]);
		std::tuple<Vec2, Vec2> cd = std::make_tuple(outerObject->points[2], outerObject->points[3]);
		std::tuple<Vec2, Vec2> da = std::make_tuple(outerObject->points[3], outerObject->points[0]);

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

	for (auto point : objectA->points)
	{
		point += (coordsA - coordsB);

		if (AlgoUtils::isPointInPolygon(objectB->points, point))
		{
			if (runCollisonEventsOnce() == CollisionObject::CollisionResult::CollideWithPhysics)
			{
				resolve(objectA, objectB, point);
			}
		}
	}

	for (auto point : objectB->points)
	{
		point += (coordsB - coordsA);

		if (AlgoUtils::isPointInPolygon(objectA->points, point))
		{
			if (runCollisonEventsOnce() == CollisionObject::CollisionResult::CollideWithPhysics)
			{
				resolve(objectB, objectA,  point);
			}
		}
	}
}

void CollisionResolver::polyToPoly(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
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

	CollisionObject::CollisionResult collisionResult = CollisionObject::CollisionResult::DoNothing;

	if (std::any_of(objectA->points.begin(), objectA->points.end(), [=](Vec2 point)
		{
			point += (coordsA - coordsB);

			return AlgoUtils::isPointInPolygon(objectB->points, point);
		})
		|| std::any_of(objectB->points.begin(), objectB->points.end(), [=](Vec2 point)
		{
			point += (coordsB - coordsA);
			
			return AlgoUtils::isPointInPolygon(objectA->points, point);
		}))
	{
		collisionResult = onCollision();
	}

	if (collisionResult != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	bool hadCollision = false;

	for (auto currentSegment : objectA->segments)
	{
		currentSegment = std::make_tuple(coordsA + std::get<0>(currentSegment), coordsA + std::get<1>(currentSegment));

		for (auto otherSegment : objectA->segments)
		{
			otherSegment = std::make_tuple(coordsB + std::get<0>(otherSegment), coordsA + std::get<1>(otherSegment));

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
}

void CollisionResolver::polyToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
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
}

Vec2 CollisionResolver::applyCorrection(CollisionObject* objectA, CollisionObject* objectB, Vec2 correction, Vec2 impactNormal)
{
	correction.x *= impactNormal.x;
	correction.y *= impactNormal.y;
	
	// If X disabled, this makes for better horizontal movement, but enabled is more realistic. Might need a compromise/toggleability
	// objectA->velocity.x *= impactNormal.y;
	// objectB->velocity.x *= impactNormal.y;

	objectA->velocity.y *= impactNormal.x;
	objectB->velocity.y *= impactNormal.x;

	if (objectA->isDynamic && objectB->isDynamic)
	{
		// TODO: Instead of weighting each object equally, allow for this to be configurable (ie 75% of force to one object, 25% to other).
		// Probably via a mass parameter.
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

bool CollisionResolver::isQuadCompatible(CollisionObject* objectA)
{
	return objectA->shape == CollisionObject::Shape::Rectangle
			|| objectA->shape == CollisionObject::Shape::Quad;
}

bool CollisionResolver::isPolyCompatible(CollisionObject* objectA)
{
	return objectA->shape == CollisionObject::Shape::Polygon
			|| objectA->shape == CollisionObject::Shape::Rectangle
			|| objectA->shape == CollisionObject::Shape::Quad;
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
