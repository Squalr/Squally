#pragma once
#include <functional>
#include <stack>

#include "cocos/math/Vec2.h"

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
		cocos2d::Vec2 trackOffset = cocos2d::Vec2::ZERO,
		cocos2d::Vec2 scrollOffset = CameraTrackingData::DefaultCameraOffset,
		CameraScrollType scrollType = CameraScrollType::Rectangle,
		cocos2d::Vec2 followSpeed = CameraTrackingData::DefaultCameraFollowSpeed,
		float zoom = 1.0f,
		std::function<cocos2d::Vec2()> customPositionFunction = nullptr,
		std::string id = ""
	);

	cocos2d::Node* target = nullptr;
	cocos2d::Vec2 followSpeed = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 scrollOffset = cocos2d::Vec2::ZERO;
	CameraScrollType scrollType = CameraScrollType::Rectangle;
	cocos2d::Vec2 trackOffset = cocos2d::Vec2::ZERO;
	float zoom = 1.0f;
	std::function<cocos2d::Vec2()> customPositionFunction;
	std::string id;
	
private:
};
