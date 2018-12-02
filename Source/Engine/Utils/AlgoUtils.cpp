#include "AlgoUtils.h"

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


std::vector<AlgoUtils::Triangle> AlgoUtils::trianglefyPolygon(std::vector<Vec2> polygonPoints)
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

bool AlgoUtils::isPointInTriangle(AlgoUtils::Triangle triangle, Vec2 point)
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

std::vector<std::tuple<Vec2, Vec2>> AlgoUtils::buildSegmentsFromPoints(std::vector<Vec2> points)
{
	std::vector<std::tuple<Vec2, Vec2>> segments = std::vector<std::tuple<Vec2, Vec2>>();

	Vec2* previous = nullptr;

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

Rect AlgoUtils::getPolygonRect(std::vector<Vec2> points)
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

	return drawRect;
}