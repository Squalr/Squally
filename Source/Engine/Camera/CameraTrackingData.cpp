#include "GameCamera.h"

#include "cocos/2d/CCNode.h"

using namespace cocos2d;

const Vec2 CameraTrackingData::DefaultCameraOffset = cocos2d::Vec2(256.0f, 192.0f);
const Vec2 CameraTrackingData::DefaultCameraFollowSpeed = cocos2d::Vec2(0.015f, 0.015f);

CameraTrackingData::CameraTrackingData()
{
	this->target = nullptr;
	this->scrollOffset = Vec2::ZERO;
	this->scrollType = CameraScrollType::Rectangle;
	this->followSpeed = Vec2::ZERO;
	this->trackOffset = Vec2::ZERO;
	this->zoom = 1.0f;
	this->customPositionFunction = nullptr;
}

CameraTrackingData::CameraTrackingData(cocos2d::Node* target,
	cocos2d::Vec2 trackOffset,
	cocos2d::Vec2 scrollOffset,
	CameraScrollType scrollType,
	cocos2d::Vec2 followSpeed,
	float zoom,
	std::function<cocos2d::Vec2()> customPositionFunction)
{
	this->target = target;
	this->scrollOffset = scrollOffset;
	this->scrollType = scrollType;
	this->followSpeed = followSpeed;
	this->trackOffset = trackOffset;
	this->zoom = zoom;
	this->customPositionFunction = customPositionFunction;
}