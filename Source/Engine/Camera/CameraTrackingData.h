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
	class Node;
}

class CameraTrackingData
{
public:
	static const cocos2d::Vec2 DefaultCameraOffset;
	static const cocos2d::Vec2 DefaultCameraFollowSpeed;

	CameraTrackingData();
	CameraTrackingData(
		cocos2d::Node* target, 
		cocos2d::Vec2 scrollOffset = CameraTrackingData::DefaultCameraOffset,
		cocos2d::Vec2 followSpeed = CameraTrackingData::DefaultCameraFollowSpeed,
		cocos2d::Vec2 trackOffset = cocos2d::Vec2::ZERO, 
		std::function<cocos2d::Vec2()> customPositionFunction = nullptr
	);

	cocos2d::Node* target;
	cocos2d::Vec2 followSpeed;
	cocos2d::Vec2 scrollOffset;
	cocos2d::Vec2 trackOffset;
	std::function<cocos2d::Vec2()> customPositionFunction;
private:
};
