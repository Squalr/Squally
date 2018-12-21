#include "GameCamera.h"

#include "cocos/2d/CCNode.h"

using namespace cocos2d;

const Vec2 CameraTrackingData::DefaultCameraOffset = cocos2d::Vec2(256.0f, 192.0f);
const Vec2 CameraTrackingData::DefaultCameraFollowSpeed = cocos2d::Vec2(0.075f, 0.075f);

CameraTrackingData::CameraTrackingData()
{
}

CameraTrackingData::CameraTrackingData(cocos2d::Node* target,
	cocos2d::Vec2 scrollOffset,
	CameraScrollType scrollType,
	cocos2d::Vec2 followSpeed,
	cocos2d::Vec2 trackOffset,
	std::function<cocos2d::Vec2()> customPositionFunction)
{
	this->target = target;
	this->scrollOffset = scrollOffset;
	this->scrollType = scrollType;
	this->followSpeed = followSpeed;
	this->trackOffset = trackOffset;
	this->customPositionFunction = customPositionFunction;
}