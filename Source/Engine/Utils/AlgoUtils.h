#pragma once
#include <tuple>
#include <vector>

#include "cocos/math/CCGeometry.h"

class AlgoUtils
{
public:
	struct Triangle
	{
		cocos2d::Vec2 coords[3];

		Triangle(cocos2d::Vec2 coordA, cocos2d::Vec2 coordB, cocos2d::Vec2 coordC)
		{
			coords[0] = coordA;
			coords[1] = coordB;
			coords[2] = coordC;
		}
	};

	static cocos2d::Vec3 computeArcVelocity(cocos2d::Vec3 source, cocos2d::Vec3 destination, cocos2d::Vec3 acceleration, cocos2d::Vec3 time);
	static cocos2d::Vec2 pointOnEllipse(cocos2d::Vec2 center, float rx, float ry, cocos2d::Vec2 closestPoint);
	static std::vector<int> subsetSum(const std::vector<int>& numbers, int sum, int requiredLength);
	
	static std::vector<Triangle> trianglefyPolygon(const std::vector<cocos2d::Vec2>& polygonPoints, const std::vector<cocos2d::Vec2>& holePoints = { });
	static bool isPointInTriangle(const Triangle& triangle, cocos2d::Vec2 point);
	static std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>>
			buildSegmentsFromPoints(const std::vector<cocos2d::Vec2>& points);
	static cocos2d::Rect getPolygonRect(const std::vector<cocos2d::Vec2>& points);
	static std::vector<cocos2d::Vec2> insetPolygon(const std::vector<Triangle>& triangles,
			const std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>>& segments, float insetDistance);
	static float getSegmentAngle(std::tuple<cocos2d::Vec2, cocos2d::Vec2> segment,
			const std::vector<Triangle>& triangles, cocos2d::Node* debugDrawNode = nullptr);
	static float getSegmentNormalAngle(std::tuple<cocos2d::Vec2, cocos2d::Vec2> segment,
			const std::vector<Triangle>& triangles, cocos2d::Node* debugDrawNode = nullptr);
	static cocos2d::Vec2 getOutwardNormal(std::tuple<cocos2d::Vec2, cocos2d::Vec2> segment,
			const std::vector<Triangle>& triangles, cocos2d::Node* debugDrawNode = nullptr);
};

