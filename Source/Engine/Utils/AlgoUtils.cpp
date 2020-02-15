#include "AlgoUtils.h"

#include <set>

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"

using namespace cocos2d;

Vec3 AlgoUtils::computeArcVelocity(Vec3 source, Vec3 destination, Vec3 acceleration, Vec3 time)
{
	Vec3 velocity = (destination - source - 0.5f * Vec3(acceleration.x * time.x * time.x, acceleration.y * time.y * time.y, acceleration.z * time.z * time.z));

	velocity.x = time.x == 0.0f ? 0.0f : (velocity.x / time.x);
	velocity.y = time.y == 0.0f ? 0.0f : (velocity.y / time.y);
	velocity.z = time.z == 0.0f ? 0.0f : (velocity.z / time.z);

	return velocity;
}

Vec2 AlgoUtils::pointOnEllipse(Vec2 center, float rx, float ry, Vec2 closestPoint)
{
	int maxIterations = 10;
	float eps = 0.1f / std::max(rx, ry);

	Vec2 p1 = Vec2(closestPoint.x - center.x, closestPoint.y - center.y);

	// Intersection of straight line from origin to p with ellipse
	// as the first approximation:
	float phi = std::atan2(rx * p1.y, ry * p1.x);

	// Newton iteration to find solution of
	// f(theta) := (a^2 - b^2) cos(phi) sin(phi) - x a sin(phi) + y b cos(phi) = 0:
	for (int i = 0; i < maxIterations; i++)
	{
		// function value and derivative at phi:
		float c = std::cos(phi);
		float s = std::sin(phi);
		float f = (rx * rx - ry * ry) * c * s - p1.x * rx * s + p1.y * ry * c;
		float f1 = (rx * rx - ry * ry) * (c * c - s * s) - p1.x * rx * c - p1.y * ry * s;

		float delta = f / f1;

		phi = phi - delta;
		
		if (std::abs(delta) < eps)
		{
			break;
		}
	}

	return Vec2(center.x + rx * std::cos(phi), center.y + ry * std::sin(phi));
}

std::vector<int> AlgoUtils::subsetSum(const std::vector<int>& numbers, int sum, int requiredLength)
{
	static std::vector<int> result = std::vector<int>();
	static std::set<std::tuple<int, int>> memoization = std::set<std::tuple<int, int>>();
	static bool finished = false;
	static int closestCount = 0;
	static int closestSum = 0;

	result.clear();
	memoization.clear();
	finished = false;
	closestSum = std::numeric_limits<int>::max();
	closestCount = std::numeric_limits<int>::max();

	std::function<void(int, int, std::vector<int>)> subset_sum = [&subset_sum, numbers, sum, requiredLength](int vote_choice_index, int remainder, std::vector<int> votes)
	{
		// Solution already found
		if (finished)
		{
			return;
		}

		// No more choices left to add
		if (vote_choice_index >= int(numbers.size()))
		{
			return;
		}

		// No more possible sums
		if (remainder <= 0)
		{
			return;
		}

		// No more votes allowed
		if (int(votes.size()) > requiredLength)
		{
			return;
		}

		int next_vote = numbers[vote_choice_index];

		// Memoization (current vote average / sum remainder / # choices)
		// Note the memoization we use is an admissible heuristic
		// ie 5 + 5 + 1 is the same as 4 + 4 + 3, but we will give more weight
		// to the variant with less 5s. This is enforced by carefully ordering
		// our vote choices and recursive calls such that we can greedily memoize.
		if (votes.size() > 0)
		{
			std::tuple<int, int> signature = std::tuple<int, int>(remainder, numbers.size() - vote_choice_index);

			if (memoization.find(signature) != memoization.end())
			{
				return;
			}

			memoization.insert(signature);
		}

		// Save best solution so far (priorize closest count first, then closest sum)
		if ((requiredLength - (int(votes.size()) + 1) < closestCount) || (requiredLength - (int(votes.size()) + 1) == closestCount && remainder < closestSum))
		{
			closestCount = requiredLength - int(votes.size());
			closestSum = remainder;
			result = std::vector<int>(votes);
			result.push_back(next_vote);
		}

		// Check if we found a perfect solution
		if (next_vote == remainder && int(votes.size()) + 1 >= requiredLength)
		{
			votes.push_back(next_vote);
			result = votes;
			finished = true;
			return;
		}

		// Note: Swap the order of these two calls for an uneven distribution (high values preferred)

		// Case where we ignore the value and remove it from our choices
		std::vector<int> clonedVotes = std::vector<int>(votes);
		subset_sum(vote_choice_index + 1, remainder, clonedVotes);

		// Case where we add the value and remove it from our choices
		std::vector<int> appendedVotes = std::vector<int>(votes);
		appendedVotes.push_back(next_vote);
		subset_sum(vote_choice_index + 1, remainder - next_vote, appendedVotes);
	};

	subset_sum(0, sum, std::vector<int>());

	return result;
}

std::vector<AlgoUtils::Triangle> AlgoUtils::trianglefyPolygon(const std::vector<Vec2>& polygonPoints, const std::vector<Vec2>& holePoints)
{
	std::vector<Triangle> triangles = std::vector<Triangle>();

	uint32_t MaxPointCount = polygonPoints.size();
	size_t MemoryRequired = MPE_PolyMemoryRequired(MaxPointCount);
	void* memory = calloc(MemoryRequired, 1);
	MPEPolyContext polyContext;

	if (!MPE_PolyInitContext(&polyContext, memory, MaxPointCount))
	{
		LogUtils::logError("Error trianglefying polygon. Possible error condition: duplicate point cordinates, bounds checking assert failures");

		return triangles;
	}

	for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
	{
		Vec2 point = *it;

		// Create a version of this point for our Constrained Delauney Triangulation (CDT) library
		MPEPolyPoint* Point = MPE_PolyPushPoint(&polyContext);
		Point->X = point.x;
		Point->Y = point.y;
	}

	// Add the polyline for the edge. This will consume all points added so far.
	MPE_PolyAddEdge(&polyContext);

	if (!holePoints.empty())
	{
		MPEPolyPoint* holes = MPE_PolyPushPointArray(&polyContext, holePoints.size());

		for (int index = 0; index < int(holePoints.size()); index++)
		{
			holes[index].X = holePoints[index].x;
			holes[index].Y = holePoints[index].y;
		}

		MPE_PolyAddHole(&polyContext);
	}

	// Triangulate the shape
	MPE_PolyTriangulate(&polyContext);

	// Parse out the triangle and create the in-fill color from that
	for (uxx triangleIndex = 0; triangleIndex < polyContext.TriangleCount; ++triangleIndex)
	{
		MPEPolyTriangle* triangle = polyContext.Triangles[triangleIndex];
		DrawNode* infillTriangle = DrawNode::create();

		Vec2 trianglePointA = Vec2(triangle->Points[0]->X, triangle->Points[0]->Y);
		Vec2 trianglePointB = Vec2(triangle->Points[1]->X, triangle->Points[1]->Y);
		Vec2 trianglePointC = Vec2(triangle->Points[2]->X, triangle->Points[2]->Y);

		triangles.push_back(Triangle(trianglePointA, trianglePointB, trianglePointC));
	}

	return triangles;
}

bool AlgoUtils::isPointInTriangle(const AlgoUtils::Triangle& triangle, Vec2 point)
{
	float as_x = point.x - triangle.coords[0].x;
	float as_y = point.y - triangle.coords[0].y;
	bool s_ab = (triangle.coords[1].x - triangle.coords[0].x) * as_y - (triangle.coords[1].y - triangle.coords[0].y) * as_x > 0;

	if ((triangle.coords[2].x - triangle.coords[0].x) * as_y - (triangle.coords[2].y - triangle.coords[0].y) * as_x > 0 == s_ab ||
		(triangle.coords[2].x - triangle.coords[1].x) * (point.y - triangle.coords[1].y) - (triangle.coords[2].y - triangle.coords[1].y) * (point.x - triangle.coords[1].x) > 0 != s_ab)
	{
		return false;
	}

	return true;
}

bool AlgoUtils::isPointInPolygon(const std::vector<Vec2>& points, Vec2 point)
{
	int size = int(points.size());
	bool c = false;
	int i = 0;
	int j = 0;

	for (i = 0, j = size - 1; i < size; j = i++)
	{
		if (((points[i].y > point.y) != (points[j].y > point.y)) && (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
		{
			c = !c;
		}
	}

	return c;
}

Vec2 AlgoUtils::getClosestPointOnLine(std::tuple<Vec2, Vec2> segment, Vec2 point)
{
	Vec2 A = std::get<0>(segment);
	Vec2 B = std::get<1>(segment);

	Vec2 ap = Vec2(point.x - A.x, point.y - A.y);
	Vec2 ab = Vec2(B.x - A.x, B.y - A.y);

	float magnitude = ab.x * ab.x + ab.y * ab.y;
	float dotProd = ap.x * ab.x + ap.y * ab.y;

	if (magnitude == 0.0f)
	{
		return Vec2::ZERO;
	}

	float t = dotProd / magnitude;

	return Vec2(A.x + ab.x * t, A.y + ab.y * t);
}

float AlgoUtils::getDistanceFromSegment(std::tuple<Vec2, Vec2> segment, Vec2 point)
{
	Vec2 p1 = std::get<0>(segment);
	Vec2 p2 = std::get<1>(segment);

	float a = p1.y - p2.y;
	float b = p2.x - p1.x;
	float c = p1.x * p2.y - p2.x * p1.y;

	float denom = a * a + b * b;

	if (denom == 0.0f)
	{
		return 0.0f;
	}
	
    return std::abs(a * point.x + b * point.y + c) / std::sqrt(denom);
}

Vec2 AlgoUtils::getLineIntersectionPoint(std::tuple<Vec2, Vec2> segmentA, std::tuple<Vec2, Vec2> segmentB) 
{
	Vec2 a = std::get<0>(segmentA);
	Vec2 b = std::get<1>(segmentA);
	Vec2 c = std::get<0>(segmentB);
	Vec2 d = std::get<1>(segmentB);

	auto det = [=](float a, float b, float c, float d)
	{
		return a * d - b * c;
	};

    float detL1 = det(a.x, a.y, b.x, b.y);
    float detL2 = det(c.x, c.y, d.x, d.y);
    float x1mx2 = a.x - b.x;
    float x3mx4 = c.x - d.x;
    float y1my2 = a.y - b.y;
    float y3my4 = c.y - d.y;

    float xnom = det(detL1, x1mx2, detL2, x3mx4);
    float ynom = det(detL1, y1my2, detL2, y3my4);
    float denom = det(x1mx2, y1my2, x3mx4, y3my4);

    if(denom == 0.0)
    {
        return Vec2::ZERO;
    }

    return Vec2(xnom / denom, ynom / denom);
}

bool AlgoUtils::doSegmentsIntersect(std::tuple<Vec2, Vec2> segmentA, std::tuple<Vec2, Vec2> segmentB)
{
	auto onSegment = [](Vec2 p, Vec2 q, Vec2 r) 
	{ 
		if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && 
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		{
			return true; 	
		}

		return false; 
	};
	
	auto orientation = [](Vec2 p, Vec2 q, Vec2 r) 
	{ 
		float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
	
		if (val == 0.0f)
		{
			return 0;
		}
	
		return (val > 0.0f) ? 1 : 2;
	};

	Vec2 p1 = std::get<0>(segmentA);
	Vec2 q1 = std::get<1>(segmentA);
	Vec2 p2 = std::get<0>(segmentB);
	Vec2 q2 = std::get<1>(segmentB);

	auto det = [=](float a, float b, float c, float d)
	{
		return a * d - b * c;
	};

    float x1mx2 = p1.x - q1.x;
    float x3mx4 = p2.x - q2.x;
    float y1my2 = p1.y - q1.y;
    float y3my4 = p2.y - q2.y;

    float denom = det(x1mx2, y1my2, x3mx4, y3my4);

    if(denom == 0.0)
    {
        return false;
    }

    // Find the four orientations needed for general and special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4)
	{
        return true; 
	}
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1))
	{
		return true;
	}
  
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1))
	{
		return true;
	}
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2))
	{
		return true;
	}
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2))
	{
		return true;
	}
  
    return false;
}

std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> AlgoUtils::shrinkSegments(const std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>>& segments)
{
	const float factor = 8.0f;

	std::vector<std::tuple<Vec2, Vec2>> newSegments = std::vector<std::tuple<Vec2, Vec2>>();

	for (auto segment : segments)
	{
		const Vec2& first = std::get<0>(segment);
		const Vec2& second = std::get<1>(segment);
		const Vec2& left = first.x <= second.x ? first : second;
		const Vec2& right = first.x <= second.x ? second : first;
		const Vec2& lower = first.y <= second.y ? first : second;
		const Vec2& upper = first.y <= second.y ? second : first;

		if (left.x == right.x)
		{
			newSegments.push_back({ Vec2(lower.x, lower.y + factor), Vec2(upper.x, upper.y - factor) });
		}
		else
		{
			const float rise = std::abs(left.y - right.y);
			const float run = std::abs(left.x - right.x);
			const float angle = std::atan2(rise, run);
			const float factorX = std::cos(angle) * factor;
			const float factorY = std::sin(angle) * factor;

			newSegments.push_back({
				Vec2(left.x + factorX, left.y + (rise >= 0.0f ? factorY : -factorY)),
				Vec2(right.x - factorX, right.y + (rise <= 0.0f ? factorY : -factorY))
			});
		}
	}

	return newSegments;
}

std::vector<std::tuple<Vec2, Vec2>> AlgoUtils::buildSegmentsFromPoints(const std::vector<Vec2>& points)
{
	std::vector<std::tuple<Vec2, Vec2>> segments = std::vector<std::tuple<Vec2, Vec2>>();

	const Vec2* previous = nullptr;

	for (auto it = points.begin(); it != points.end(); it++)
	{
		if (previous != nullptr)
		{
			segments.push_back(std::tuple<Vec2, Vec2>(*previous, *it));
		}

		previous = &(*it);
	}

	// Loop to start
	if (points.size() >= 2 && points.back() != points.front())
	{
		segments.push_back(std::tuple<Vec2, Vec2>(points.back(), points[0]));
	}

	return segments;
}

Rect AlgoUtils::getPolygonRect(const std::vector<Vec2>& points)
{
	Rect drawRect = Rect::ZERO;

	for (auto it = points.begin(); it != points.end(); it++)
	{
		Vec2 point = *it;

		drawRect.origin.x = std::min(drawRect.origin.x, point.x);
		drawRect.origin.y = std::min(drawRect.origin.y, point.y);
		drawRect.size.width = std::max(drawRect.size.width, point.x);
		drawRect.size.height = std::max(drawRect.size.height, point.y);
	}

	drawRect.size.width += -drawRect.origin.x;
	drawRect.size.height += -drawRect.origin.y;

	return drawRect;
}

std::vector<Vec2> AlgoUtils::insetPolygon(const std::vector<Triangle>& triangles,
		const std::vector<std::tuple<Vec2, Vec2>>& segments, float insetDistance)
{
	std::vector<Vec2> insetPolygonPoints = std::vector<Vec2>();

	for (auto it = segments.begin(); it != segments.end(); it++)
	{
		auto itClone = it;

		std::tuple<Vec2, Vec2> segment = *it;
		std::tuple<Vec2, Vec2> nextSegment = (++itClone) == segments.end() ? segments[0] : (*itClone);

		Vec2 normalA = AlgoUtils::getOutwardNormal(segment, triangles);
		Vec2 normalB = AlgoUtils::getOutwardNormal(nextSegment, triangles);
		Vec2 delta = ((normalA + normalB) / 2.0f).getNormalized() * insetDistance;
		Vec2 infillPoint = std::get<1>(segment) - delta;

		insetPolygonPoints.push_back(infillPoint);
	}

	return insetPolygonPoints;
}

float AlgoUtils::getSegmentAngle(std::tuple<Vec2, Vec2> segment, const std::vector<AlgoUtils::Triangle>& triangles,
		DrawNode* debugDrawNode)
{
	float angle = AlgoUtils::getSegmentNormalAngle(segment, triangles, debugDrawNode);

	// Because we used the outward normal to find the angle, correct the angle by 90 degrees
	angle += float(M_PI) / 2.0f;

	// Make it positive for my sanity
	angle = std::fmod(angle, 2.0f * float(M_PI));

	if (angle < 0)
	{
		angle += 2.0f * float(M_PI);
	}

	return angle;
}

Vec2 AlgoUtils::getSegmentNormal(std::tuple<cocos2d::Vec2, cocos2d::Vec2> segment)
{
	Vec2 delta = std::get<0>(segment) - std::get<1>(segment);

	delta.normalize();

	return Vec2(std::abs(delta.y), std::abs(delta.x));
}

float AlgoUtils::getSegmentNormalAngle(std::tuple<Vec2, Vec2> segment,
		const std::vector<AlgoUtils::Triangle>& triangles, DrawNode* debugDrawNode)
{
	Vec2 outwardNormal = AlgoUtils::getOutwardNormal(segment, triangles, debugDrawNode);
	float angle = std::atan2(outwardNormal.y, outwardNormal.x);

	// Make it positive for my sanity
	angle = std::fmod(angle, 2.0f * float(M_PI));

	if (angle < 0)
	{
		angle += 2.0f * float(M_PI);
	}

	return angle;
}

Vec2 AlgoUtils::getOutwardNormal(std::tuple<Vec2, Vec2> segment, const std::vector<AlgoUtils::Triangle>& triangles,
		DrawNode* debugDrawNode)
{
	// Distance used to check which direction is "inside" the polygon
	const float INNER_NORMAL_COLLISION_TEST_DISTANCE = 48.0f;

	Vec2 source = std::get<0>(segment);
	Vec2 dest = std::get<1>(segment);
	Vec2 delta = dest - source;
	Vec2 midPoint = source.getMidpoint(dest);
	Vec2 outwardNormal = Vec2(-delta.getNormalized().y, delta.getNormalized().x);
	Vec2 candidateTestingPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * outwardNormal;

	// There are two possible normals -- check if the one we picked is the surface normal
	for (auto it = triangles.begin(); it != triangles.end(); it++)
	{
		AlgoUtils::Triangle triangle = *it;

		if (AlgoUtils::isPointInTriangle(triangle, candidateTestingPoint))
		{
			// We chose an inward normal instead of an outward normal -- fix it
			outwardNormal *= -1.0f;
			break;
		}
	}

	if (debugDrawNode != nullptr)
	{
		Vec2 outwardNormalPoint = midPoint + INNER_NORMAL_COLLISION_TEST_DISTANCE * outwardNormal;
		
		debugDrawNode->drawDot(source, 4.0f, Color4F::BLUE);
		debugDrawNode->drawLine(midPoint, outwardNormalPoint, Color4F::YELLOW);
		debugDrawNode->drawDot(outwardNormalPoint, 4.0f, Color4F::YELLOW);
		debugDrawNode->drawLine(midPoint, candidateTestingPoint, Color4F::GREEN);
		debugDrawNode->drawDot(candidateTestingPoint, 3.0f, Color4F::GREEN);
		debugDrawNode->drawDot(midPoint, 8.0f, Color4F::MAGENTA);
	}

	return outwardNormal;
}
