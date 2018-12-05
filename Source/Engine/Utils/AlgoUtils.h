#pragma once
#include "cocos2d.h"

#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"

using namespace cocos2d;

class AlgoUtils
{
public:
	struct Triangle;

	static std::vector<int> subsetSum(const std::vector<int>& numbers, int sum, int requiredLength);
	static std::vector<Triangle> trianglefyPolygon(std::vector<Vec2> polygonPoints);
	static bool isPointInTriangle(Triangle triangle, Vec2 point);
	static std::vector<std::tuple<Vec2, Vec2>> buildSegmentsFromPoints(std::vector<Vec2> points);
	static Rect getPolygonRect(std::vector<Vec2> points);
	static std::vector<Vec2> insetPolygon(std::vector<Triangle> triangles, std::vector<std::tuple<Vec2, Vec2>> segments, float insetDistance);
	static float getSegmentAngle(std::tuple<Vec2, Vec2> segment, std::vector<Triangle> triangles, Node* debugDrawNode = nullptr);
	static float getSegmentNormalAngle(std::tuple<Vec2, Vec2> segment, std::vector<Triangle> triangles, Node* debugDrawNode = nullptr);
	static Vec2 getOutwardNormal(std::tuple<Vec2, Vec2> segment, std::vector<Triangle> triangles, Node* debugDrawNode = nullptr);

	struct Triangle
	{
		Vec2 coords[3];

		Triangle(Vec2 coordA, Vec2 coordB, Vec2 coordC)
		{
			coords[0] = coordA;
			coords[1] = coordB;
			coords[2] = coordC;
		}
	};
};

