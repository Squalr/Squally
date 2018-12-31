#include "CameraFocus.h"

#include "Engine/Camera/GameCamera.h"

using namespace cocos2d;

const std::string CameraFocus::MapKeyCameraFocus = "camera-focus";

CameraFocus* CameraFocus::create(ValueMap* initProperties)
{
	CameraFocus* instance = new CameraFocus(initProperties);

	instance->autorelease();

	return instance;
}

CameraFocus::CameraFocus(ValueMap* initProperties) : SerializableObject(initProperties)
{
}

CameraFocus::~CameraFocus()
{
}

void CameraFocus::onEnter()
{
	super::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(this, Vec2(0.0f, 0.0f), CameraTrackingData::CameraScrollType::Rectangle, Vec2::ZERO);
	GameCamera::getInstance()->setTarget(trackingData);
}
