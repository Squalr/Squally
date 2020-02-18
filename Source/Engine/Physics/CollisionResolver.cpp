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
	
	Rect rectA = objectA->boundsRect;
	Rect rectB = objectB->boundsRect;

	rectA.origin += coordsA;
	rectB.origin += coordsB;

	// Cheap and easy bounds check
	if (!rectA.intersectsRect(rectB))
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
	
	Rect rectA = objectA->boundsRect;
	Rect rectB = objectB->boundsRect;

	rectA.origin += coordsA;
	rectB.origin += coordsB;

	// Cheap and easy bounds check
	if (!rectA.intersectsRect(rectB))
	{
		return;
	}

	if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	Vec2 correction = Vec2(
		rectA.origin.x <= rectB.origin.x
			? (rectB.getMinX() - rectA.getMaxX())
			: (rectB.getMaxX() - rectA.getMinX()),
		rectA.origin.y <= rectB.origin.y
			? (rectB.getMinY() - rectA.getMaxY())
			: (rectB.getMaxY() - rectA.getMinY())
	);

	if (correction.x == 0.0f || correction.y == 0.0f)
	{
		return;
	}

	Vec2 normal = Vec2(std::abs(correction.x), std::abs(correction.y));

	normal.x = normal.x > normal.y ? 0.0f : normal.x;
	normal.y = normal.y > std::abs(correction.x) ? 0.0f : normal.y;

	normal.normalize();

	CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
}

void CollisionResolver::quadToQuad(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
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

	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);
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
	CollisionObject::CollisionResult result = CollisionObject::CollisionResult::DoNothing;

	// Collision check by determining if any points from either polygon is contained by the other polygon
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
		result = onCollision();
	}

	if (result != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	// More detailed detection with collisions
	for (auto objectASegment : objectA->segments)
	{
		objectASegment = std::make_tuple(coordsA + std::get<0>(objectASegment), coordsA + std::get<1>(objectASegment));

		for (auto objectBSegment : objectB->segments)
		{
			objectBSegment = std::make_tuple(coordsB + std::get<0>(objectBSegment), coordsB + std::get<1>(objectBSegment));

			if (!AlgoUtils::doSegmentsIntersect(objectASegment, objectBSegment))
			{
				continue;
			}
			
			Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(objectASegment, objectBSegment);
			float objectADistanceP1 = std::get<0>(objectASegment).distance(intersectionPoint);
			float objectADistanceP2 = std::get<1>(objectASegment).distance(intersectionPoint);
			float objectBDistanceP1 = std::get<0>(objectBSegment).distance(intersectionPoint);
			float objectBDistanceP2 = std::get<1>(objectBSegment).distance(intersectionPoint);

			Vec2 correction = Vec2::ZERO;
			Vec2 normal = Vec2::ZERO;

			// CollisionResolver::spawnDebugPoint(objectA, intersectionPoint);

			if (std::min(objectADistanceP1, objectADistanceP2) < std::min(objectBDistanceP1, objectBDistanceP2))
			{
				// Case 1: The end of this segment is close to the intersection point. Snap the end of this segment to intersect the other segment.
				normal = AlgoUtils::getSegmentNormal(objectBSegment);

				// CollisionResolver::spawnDebugVector(objectA, std::get<0>(objectASegment), std::get<1>(objectASegment), Color4F::GREEN);

				if (objectADistanceP1 < objectADistanceP2)
				{
					correction = intersectionPoint - std::get<0>(objectASegment);
				}
				else
				{
					correction = intersectionPoint - std::get<1>(objectASegment);
				}
			}
			else
			{
				// Case 2: The end of the other segment is closer to the intersection point. The other object can't snap since it's static,
				// so instead we need to push this object away by a calculated amount
				normal = AlgoUtils::getSegmentNormal(objectASegment);

				// CollisionResolver::spawnDebugVector(objectA, std::get<0>(objectBSegment), std::get<1>(objectBSegment), Color4F::BLUE);

				if (objectBDistanceP1 < objectBDistanceP2)
				{
					correction = std::get<0>(objectBSegment) - intersectionPoint;
				}
				else
				{
					correction = std::get<1>(objectBSegment) - intersectionPoint;
				}
			}

			coordsA += CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
		}
	}
}

void CollisionResolver::polyToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);
	std::tuple<Vec2, Vec2> objectBSegment = std::make_tuple(coordsB + std::get<0>(objectB->segments[0]), coordsB + std::get<1>(objectB->segments[0]));
	bool hadCollision = false;

	for (auto objectASegment : objectA->segments)
	{
		objectASegment = std::make_tuple(coordsA + std::get<0>(objectASegment), coordsA + std::get<1>(objectASegment));

		if (!AlgoUtils::doSegmentsIntersect(objectASegment, objectBSegment))
		{
			continue;
		}

		if (!hadCollision)
		{
			if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
			{
				return;
			}

			hadCollision = true;
		}

		Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(objectASegment, objectBSegment);
		float objectADistanceP1 = std::get<0>(objectASegment).distance(intersectionPoint);
		float objectADistanceP2 = std::get<1>(objectASegment).distance(intersectionPoint);
		float objectBDistanceP1 = std::get<0>(objectBSegment).distance(intersectionPoint);
		float objectBDistanceP2 = std::get<1>(objectBSegment).distance(intersectionPoint);

		Vec2 correction = Vec2::ZERO;
		Vec2 normal = Vec2::ZERO;

		// CollisionResolver::spawnDebugPoint(objectA, intersectionPoint);

		if (std::min(objectADistanceP1, objectADistanceP2) < std::min(objectBDistanceP1, objectBDistanceP2))
		{
			// Case 1: The end of this segment is close to the intersection point. Snap the end of this segment to intersect the other segment.
			normal = AlgoUtils::getSegmentNormal(objectBSegment);

			// CollisionResolver::spawnDebugVector(objectA, std::get<0>(objectASegment), std::get<1>(objectASegment), Color4F::GREEN);

			if (objectADistanceP1 < objectADistanceP2)
			{
				correction = intersectionPoint - std::get<0>(objectASegment);
			}
			else
			{
				correction = intersectionPoint - std::get<1>(objectASegment);
			}
		}
		else
		{
			// Case 2: The end of the other segment is closer to the intersection point. The other object can't snap since it's static,
			// so instead we need to push this object away by a calculated amount
			normal = AlgoUtils::getSegmentNormal(objectASegment);

			// CollisionResolver::spawnDebugVector(objectA, std::get<0>(objectBSegment), std::get<1>(objectBSegment), Color4F::BLUE);

			if (objectBDistanceP1 < objectBDistanceP2)
			{
				correction = std::get<0>(objectBSegment) - intersectionPoint;
			}
			else
			{
				correction = std::get<1>(objectBSegment) - intersectionPoint;
			}
		}
		
		coordsA += CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
	}
}

void CollisionResolver::segmentToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = GameUtils::getWorldCoords(objectA);
	Vec2 coordsB = GameUtils::getWorldCoords(objectB);

	std::tuple<Vec2, Vec2> objectASegment = std::make_tuple(coordsA + std::get<0>(objectA->segments[0]), coordsA + std::get<1>(objectA->segments[0]));
	std::tuple<Vec2, Vec2> objectBSegment = std::make_tuple(coordsB + std::get<0>(objectB->segments[0]), coordsB + std::get<1>(objectB->segments[0]));
	
	if (!AlgoUtils::doSegmentsIntersect(objectASegment, objectBSegment))
	{
		return;
	}

	if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(objectASegment, objectBSegment);
	float objectADistanceP1 = std::get<0>(objectASegment).distance(intersectionPoint);
	float objectADistanceP2 = std::get<1>(objectASegment).distance(intersectionPoint);
	float objectBDistanceP1 = std::get<0>(objectBSegment).distance(intersectionPoint);
	float objectBDistanceP2 = std::get<1>(objectBSegment).distance(intersectionPoint);

	Vec2 correction = Vec2::ZERO;
	Vec2 normal = Vec2::ZERO;

	if (std::min(objectADistanceP1, objectADistanceP2) < std::min(objectBDistanceP1, objectBDistanceP2))
	{
		// Case 1: The end of this segment is close to the intersection point. Snap the end of this segment to intersect the other segment.
		normal = AlgoUtils::getSegmentNormal(objectBSegment);

		if (objectADistanceP1 < objectADistanceP2)
		{
			correction = intersectionPoint - std::get<0>(objectASegment);
		}
		else
		{
			correction = intersectionPoint - std::get<1>(objectASegment);
		}
	}
	else
	{
		// Case 2: The end of the other segment is closer to the intersection point. The other object can't snap since it's static,
		// so instead we need to push this object away by a calculated amount
		normal = AlgoUtils::getSegmentNormal(objectASegment);

		if (objectBDistanceP1 < objectBDistanceP2)
		{
			correction = std::get<0>(objectBSegment) - intersectionPoint;
		}
		else
		{
			correction = std::get<1>(objectBSegment) - intersectionPoint;
		}
	}

	CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
}

Vec2 CollisionResolver::applyCorrection(CollisionObject* objectA, CollisionObject* objectB, Vec2 correction, Vec2 impactNormal)
{
	correction.x *= impactNormal.x;
	correction.y *= impactNormal.y;

	// Handle dynamic <=> dynamic collisions differently
	if (objectA->collisionProperties.isDynamic && objectB->collisionProperties.isDynamic)
	{
		float massSum = objectA->collisionProperties.mass + objectB->collisionProperties.mass;

		massSum = massSum == 0.0f ? 1.0f : massSum;

		float ratioA = (objectB->collisionProperties.mass / massSum);
		float ratioB = (objectA->collisionProperties.mass / massSum);
		
		// Apply corrections proportional to object masses
		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + correction * ratioA);
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() - correction * ratioB);
	}
	else
	{
		// If X disabled, this makes for better horizontal movement, but enabled is more realistic. Might need a compromise/toggleability
		// objectA->velocity.x *= impactNormal.y;
		// objectB->velocity.x *= impactNormal.y;

		objectA->velocity.y *= impactNormal.x;
		objectB->velocity.y *= impactNormal.x;

		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + ((objectA->collisionProperties.isDynamic) ? correction : Vec2::ZERO));
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() + ((objectB->collisionProperties.isDynamic) ? correction : Vec2::ZERO));
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
