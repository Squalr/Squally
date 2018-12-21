#include "AlgoUtils.h"

#include <set>

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"

using namespace cocos2d;

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
		if (vote_choice_index >= numbers.size())
		{
			return;
		}

		// No more possible sums
		if (remainder <= 0)
		{
			return;
		}

		// No more votes allowed
		if (votes.size() > requiredLength)
		{
			return;
		}

		int next_vote = numbers[vote_choice_index];

		// Memoization (current vote average / sum remainder / # choices)
		// Note the memoization we use is an admissible heuristic
		// ie 5 + 5 + 1 is the same as 4 + 4 + 3, but we will give more weight
		// to the variant with more 5s. This is enforced by carefully ordering
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
		if ((requiredLength - (votes.size() + 1) < closestCount) || (requiredLength - (votes.size() + 1) == closestCount && remainder < closestSum))
		{
			closestCount = requiredLength - votes.size();
			closestSum = remainder;
			result = std::vector<int>(votes);
			result.push_back(next_vote);
		}

		// Check if we found a perfect solution
		if (next_vote == remainder && votes.size() + 1 >= requiredLength)
		{
			votes.push_back(next_vote);
			result = votes;
			finished = true;
			return;
		}

		// Case where we add the value and remove it from our choices
		std::vector<int> appendedVotes = std::vector<int>(votes);
		appendedVotes.push_back(next_vote);
		subset_sum(vote_choice_index + 1, remainder - next_vote, appendedVotes);

		// Case where we ignore the value and remove it from our choices
		std::vector<int> clonedVotes = std::vector<int>(votes);
		subset_sum(vote_choice_index + 1, remainder, clonedVotes);
	};

	subset_sum(0, sum, std::vector<int>());

	return result;
}


std::vector<AlgoUtils::Triangle> AlgoUtils::trianglefyPolygon(const std::vector<Vec2>& polygonPoints)
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
	int as_x = point.x - triangle.coords[0].x;
	int as_y = point.y - triangle.coords[0].y;
	bool s_ab = (triangle.coords[1].x - triangle.coords[0].x) * as_y - (triangle.coords[1].y - triangle.coords[0].y) * as_x > 0;

	if ((triangle.coords[2].x - triangle.coords[0].x) * as_y - (triangle.coords[2].y - triangle.coords[0].y) * as_x > 0 == s_ab ||
		(triangle.coords[2].x - triangle.coords[1].x) * (point.y - triangle.coords[1].y) - (triangle.coords[2].y - triangle.coords[1].y) * (point.x - triangle.coords[1].x) > 0 != s_ab)
	{
		return false;
	}

	return true;
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
	if (points.size() >= 2)
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
		Node* debugDrawNode)
{
	float angle = AlgoUtils::getSegmentNormalAngle(segment, triangles, debugDrawNode);

	// Because we used the outward normal to find the angle, correct the angle by 90 degrees
	angle += M_PI / 2.0f;

	// Make it positive for my sanity
	angle = std::fmod(angle, 2.0f * M_PI);

	if (angle < 0)
	{
		angle += 2.0f * M_PI;
	}

	return angle;
}

float AlgoUtils::getSegmentNormalAngle(std::tuple<Vec2, Vec2> segment,
		const std::vector<AlgoUtils::Triangle>& triangles, Node* debugDrawNode)
{
	Vec2 outwardNormal = AlgoUtils::getOutwardNormal(segment, triangles, debugDrawNode);
	float angle = std::atan2(outwardNormal.y, outwardNormal.x);

	// Make it positive for my sanity
	angle = std::fmod(angle, 2.0f * M_PI);

	if (angle < 0)
	{
		angle += 2.0f * M_PI;
	}

	return angle;
}

Vec2 AlgoUtils::getOutwardNormal(std::tuple<Vec2, Vec2> segment, const std::vector<AlgoUtils::Triangle>& triangles,
		Node* debugDrawNode)
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

		DrawNode* sourcePointDebug = DrawNode::create();
		DrawNode* midPointDebug = DrawNode::create();
		DrawNode* candidateNormalDebug = DrawNode::create(1.0f);
		DrawNode* normalDebug = DrawNode::create();

		sourcePointDebug->drawDot(source, 4.0f, Color4F::BLUE);
		normalDebug->drawLine(midPoint, outwardNormalPoint, Color4F::YELLOW);
		normalDebug->drawDot(outwardNormalPoint, 4.0f, Color4F::YELLOW);
		candidateNormalDebug->drawLine(midPoint, candidateTestingPoint, Color4F::GREEN);
		candidateNormalDebug->drawDot(candidateTestingPoint, 3.0f, Color4F::GREEN);
		midPointDebug->drawDot(midPoint, 8.0f, Color4F::MAGENTA);

		debugDrawNode->addChild(sourcePointDebug);
		debugDrawNode->addChild(normalDebug);
		debugDrawNode->addChild(candidateNormalDebug);
		debugDrawNode->addChild(midPointDebug);
	}

	return outwardNormal;
}
