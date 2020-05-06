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

	objectA->computeWorldCoords();
	objectB->computeWorldCoords();

	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
	
	Rect rectA = objectA->boundsRect;
	Rect rectB = objectB->boundsRect;

	rectA.origin += coordsA;
	rectB.origin += coordsB;

	// Cheap and easy bounds check
	if (!rectA.intersectsRect(rectB))
	{
		return;
	}

	if (objectA->shape == CollisionObject::Shape::Rectangle && objectB->shape == CollisionObject::Shape::Segment)
	{
		CollisionResolver::rectToSegment(objectA, objectB, onCollision);
	}
	else if (objectA->shape == CollisionObject::Shape::Segment && objectB->shape == CollisionObject::Shape::Rectangle)
	{
		CollisionResolver::rectToSegment(objectB, objectA, onCollision);
	}
	else if (objectA->shape == CollisionObject::Shape::Rectangle && objectB->shape == CollisionObject::Shape::Rectangle)
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
	const float thisDepthCenter = GameUtils::getDepth(collisionObjectA);
	const float otherDepthCenter = GameUtils::getDepth(collisionObjectB);

	// Ensure a < b and c < d
	const float a = thisDepthCenter - collisionObjectA->collisionDepth;
	const float b = thisDepthCenter + collisionObjectA->collisionDepth;

	const float c = otherDepthCenter - collisionObjectB->collisionDepth;
	const float d = otherDepthCenter + collisionObjectB->collisionDepth;

	// https://stackoverflow.com/questions/15726825/find-overlap-between-collinear-lines
	return b - c >= 0 && d - a >= 0.0f;
}

void CollisionResolver::rectToSegment(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
	
	Rect rectA = objectA->boundsRect;
	Rect rectB = objectB->boundsRect;

	rectA.origin += coordsA;
	rectB.origin += coordsB;

	// Cheap and easy bounds check
	if (!rectA.intersectsRect(rectB))
	{
		return;
	}

	std::tuple<Vec2, Vec2> objectBSegment = std::make_tuple(coordsB + std::get<0>(objectB->segmentsRotated[0]), coordsB + std::get<1>(objectB->segmentsRotated[0]));
	Vec2 pointB1 = std::get<0>(objectBSegment);
	Vec2 pointB2 = std::get<1>(objectBSegment);
	bool containsA = rectA.containsPoint(pointB1);
	bool containsB = rectA.containsPoint(pointB2);

	// Check for rectangle <=> segment intersection criteria
	if (!std::any_of(objectA->segmentsRotated.begin(), objectA->segmentsRotated.end(), [=](std::tuple<cocos2d::Vec2, cocos2d::Vec2> objectASegment)
		{
			objectASegment = std::make_tuple(coordsA + std::get<0>(objectASegment), coordsA + std::get<1>(objectASegment));

			return AlgoUtils::doSegmentsIntersect(objectASegment, objectBSegment);
		})
		&& !containsA
		&& !containsB)
	{
		return;
	}
	
	bool adjacent = false;
	int intersectionCount = 0;
	Vec2 intersectionA = Vec2::ZERO;
	Vec2 intersectionB = Vec2::ZERO;

	// Case 1) Check for two intersections
	for (auto objectASegment : objectA->segmentsRotated)
	{
		objectASegment = std::make_tuple(coordsA + std::get<0>(objectASegment), coordsA + std::get<1>(objectASegment));
	
		if (AlgoUtils::doSegmentsIntersect(objectASegment, objectBSegment))
		{
			intersectionA = intersectionCount == 0 ? AlgoUtils::getLineIntersectionPoint(objectASegment, objectBSegment) : intersectionA;
			intersectionB = intersectionCount == 1 ? AlgoUtils::getLineIntersectionPoint(objectASegment, objectBSegment) : intersectionB;

			if (++intersectionCount == 2)
			{
				break;
			}

			adjacent = true;
		}
		else
		{
			adjacent = false;
		}
	}

	auto calculateCorrection = [&](const Vec2& focal, bool unidirectional)
	{
		float leftDist = std::abs(focal.x - rectA.getMinX());
		float rightDist = std::abs(focal.x - rectA.getMaxX());
		float bottomDist = std::abs(focal.y - rectA.getMinY());
		float topDist = std::abs(focal.y - rectA.getMaxY());
		float xDist = std::min(leftDist, rightDist);
		float yDist = std::min(bottomDist, topDist);

		if (unidirectional)
		{
			if (xDist < yDist)
			{
				return Vec2(leftDist < rightDist ? leftDist : -rightDist, 0.0f);
			}
			else
			{
				return Vec2(0.0f, bottomDist < topDist ? bottomDist : -topDist);
			}
		}
		else
		{
			return Vec2(leftDist < rightDist ? leftDist : -rightDist, bottomDist < topDist ? bottomDist : -topDist);
		}
	};

	if (intersectionCount == 2)
	{
		if (onCollision() != CollisionObject::CollisionResult::CollideWithPhysics)
		{
			return;
		}

		Vec2 correction = calculateCorrection((intersectionA + intersectionB) / 2.0f, !adjacent);
		Vec2 normal = Vec2(std::abs(correction.x), std::abs(correction.y));

		if (adjacent)
		{
			normal.x = normal.x > normal.y ? 0.0f : normal.x;
			normal.y = normal.y > std::abs(correction.x) ? 0.0f : normal.y;
		}
		
		normal.normalize();

		if (normal != Vec2::ZERO)
		{
			CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
		}

		return;
	}

	// Case 2: Check for segment end(s) being encapsulated by rectangle
	/*
	if (containsA || containsB)
	{
		Vec2 focal = (containsA && containsB)
			? ((pointB1 + pointB2) / 2.0f)
			: (containsA ? pointB1 : pointB2);
		Vec2 correction = calculateCorrection(focal, true);
		Vec2 normal = Vec2(std::abs(correction.x), std::abs(correction.y));
		
		normal.normalize();

		if (normal != Vec2::ZERO)
		{
			CollisionResolver::applyCorrection(objectA, objectB, correction, normal);
		}
	}*/

	// Falling back on poly <=> poly, case 2 is buggy
	CollisionResolver::polyToPoly(objectA, objectB, onCollision);
}

void CollisionResolver::rectToRect(CollisionObject* objectA, CollisionObject* objectB, std::function<CollisionObject::CollisionResult()> onCollision)
{
	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
	
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
		std::tuple<Vec2, Vec2> ab = std::make_tuple(outerObject->pointsRotated[0], outerObject->pointsRotated[1]);
		std::tuple<Vec2, Vec2> bc = std::make_tuple(outerObject->pointsRotated[1], outerObject->pointsRotated[2]);
		std::tuple<Vec2, Vec2> cd = std::make_tuple(outerObject->pointsRotated[2], outerObject->pointsRotated[3]);
		std::tuple<Vec2, Vec2> da = std::make_tuple(outerObject->pointsRotated[3], outerObject->pointsRotated[0]);

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

	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
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

	for (auto point : objectA->pointsRotated)
	{
		point += (coordsA - coordsB);

		if (AlgoUtils::isPointInPolygon(objectB->pointsRotated, point))
		{
			if (runCollisonEventsOnce() == CollisionObject::CollisionResult::CollideWithPhysics)
			{
				resolve(objectA, objectB, point);
			}
		}
	}

	for (auto point : objectB->pointsRotated)
	{
		point += (coordsB - coordsA);

		if (AlgoUtils::isPointInPolygon(objectA->pointsRotated, point))
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
	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
	CollisionObject::CollisionResult result = CollisionObject::CollisionResult::DoNothing;

	// Collision check by determining if any points from either polygon is contained by the other polygon
	if (std::any_of(objectA->pointsRotated.begin(), objectA->pointsRotated.end(), [=](Vec2 point)
		{
			point += (coordsA - coordsB);

			return AlgoUtils::isPointInPolygon(objectB->pointsRotated, point);
		})
		|| std::any_of(objectB->pointsRotated.begin(), objectB->pointsRotated.end(), [=](Vec2 point)
		{
			point += (coordsB - coordsA);
			
			return AlgoUtils::isPointInPolygon(objectA->pointsRotated, point);
		}))
	{
		result = onCollision();
	}

	if (result != CollisionObject::CollisionResult::CollideWithPhysics)
	{
		return;
	}

	// More detailed detection with collisions
	for (auto objectASegment : objectA->segmentsRotated)
	{
		objectASegment = std::make_tuple(coordsA + std::get<0>(objectASegment), coordsA + std::get<1>(objectASegment));

		for (auto objectBSegment : objectB->segmentsRotated)
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
	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;
	std::tuple<Vec2, Vec2> objectBSegment = std::make_tuple(coordsB + std::get<0>(objectB->segmentsRotated[0]), coordsB + std::get<1>(objectB->segmentsRotated[0]));
	bool hadCollision = false;

	for (auto objectASegment : objectA->segmentsRotated)
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
	Vec2 coordsA = objectA->cachedWorldCoords;
	Vec2 coordsB = objectB->cachedWorldCoords;

	std::tuple<Vec2, Vec2> objectASegment = std::make_tuple(coordsA + std::get<0>(objectA->segmentsRotated[0]), coordsA + std::get<1>(objectA->segmentsRotated[0]));
	std::tuple<Vec2, Vec2> objectBSegment = std::make_tuple(coordsB + std::get<0>(objectB->segmentsRotated[0]), coordsB + std::get<1>(objectB->segmentsRotated[0]));
	
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
	float softness = (objectA->collisionProperties.softness + objectB->collisionProperties.softness) / 2.0f;

	correction.x *= (impactNormal.x * softness);
	correction.y *= impactNormal.y;

	Vec3 correction3d = Vec3(correction.x, correction.y, 0.0f);

	// Handle dynamic <=> dynamic collisions differently
	if (objectA->collisionProperties.isDynamic && objectB->collisionProperties.isDynamic)
	{
		float massSum = objectA->collisionProperties.mass + objectB->collisionProperties.mass;

		massSum = massSum == 0.0f ? 1.0f : massSum;

		float ratioA = (objectB->collisionProperties.mass / massSum);
		float ratioB = (objectA->collisionProperties.mass / massSum);
		
		// Apply corrections proportional to object masses
		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + correction3d * ratioA);
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() - correction3d * ratioB);
	}
	else
	{
		// If X disabled, this makes for better horizontal movement, but enabled is more realistic. Might need a compromise/toggleability
		// objectA->velocity.x *= impactNormal.y;
		// objectB->velocity.x *= impactNormal.y;

		objectA->velocity.y *= impactNormal.x;
		objectB->velocity.y *= impactNormal.x;

		objectA->setThisOrBindPosition(objectA->getThisOrBindPosition() + ((objectA->collisionProperties.isDynamic) ? correction3d : Vec3::ZERO));
		objectB->setThisOrBindPosition(objectB->getThisOrBindPosition() + ((objectB->collisionProperties.isDynamic) ? correction3d : Vec3::ZERO));
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

void CollisionResolver::spawnDebugShapes(CollisionObject* objectA)
{
	DrawNode* dbgA = DrawNode::create();

	for (auto next : objectA->segmentsRotated)
	{
		dbgA->drawLine(std::get<0>(next), std::get<1>(next), Color4F(Color4F::YELLOW.r, Color4F::YELLOW.g, Color4F::YELLOW.b, 0.4f));
	}

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		objectA,
		dbgA,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Retain,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	dbgA->setPosition3D(GameUtils::getWorldCoords3D(objectA));
}
