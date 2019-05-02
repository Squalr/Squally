#pragma once
#include <functional>
#include <stack>

#include "cocos/math/CCGeometry.h"
#include "cocos/math/Vec2.h"

#include "Engine/GlobalNode.h"

class Hud;

namespace cocos2d
{
	class Node;
}

class CameraTrackingData
{
public:
	static const cocos2d::Vec2 DefaultCameraOffset;
	static const cocos2d::Vec2 DefaultCameraFollowSpeed;

	enum class CameraScrollType
	{
		Rectangle,
		Ellipse
	};

	CameraTrackingData();
	CameraTrackingData(
		cocos2d::Node* target,
		cocos2d::Vec2 scrollOffset = CameraTrackingData::DefaultCameraOffset,
		CameraScrollType scrollType = CameraScrollType::Rectangle,
		cocos2d::Vec2 followSpeed = CameraTrackingData::DefaultCameraFollowSpeed,
		cocos2d::Vec2 trackOffset = cocos2d::Vec2::ZERO,
		float zoom = 1.0f,
		std::function<cocos2d::Vec2()> customPositionFunction = nullptr
	);

	cocos2d::Node* target;
	cocos2d::Vec2 followSpeed;
	cocos2d::Vec2 scrollOffset;
	CameraScrollType scrollType;
	cocos2d::Vec2 trackOffset;
	float zoom;
	std::function<cocos2d::Vec2()> customPositionFunction;
private:
};
