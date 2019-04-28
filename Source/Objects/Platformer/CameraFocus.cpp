#include "CameraFocus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CameraFocus::MapKeyCameraFocus = "camera-focus";
const std::string CameraFocus::MapKeyScrollBoundsX = "scroll-bounds-x";
const std::string CameraFocus::MapKeyScrollBoundsY = "scroll-bounds-y";
const std::string CameraFocus::MapKeyScrollSpeedX = "scroll-speed-x";
const std::string CameraFocus::MapKeyScrollSpeedY = "scroll-speed-y";
const std::string CameraFocus::MapKeyScrollType = "scroll-type";

CameraFocus* CameraFocus::create(ValueMap& initProperties)
{
	CameraFocus* instance = new CameraFocus(initProperties);

	instance->autorelease();

	return instance;
}

CameraFocus::CameraFocus(ValueMap& initProperties) : SerializableObject(initProperties)
{
	this->scrollBounds = Vec2(
		GameUtils::getKeyOrDefault(initProperties, CameraFocus::MapKeyScrollBoundsX, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(initProperties, CameraFocus::MapKeyScrollBoundsY, Value(0.0f)).asFloat()
	);
	this->scrollSpeed = Vec2(
		GameUtils::getKeyOrDefault(initProperties, CameraFocus::MapKeyScrollSpeedX, Value(CameraTrackingData::DefaultCameraFollowSpeed.x)).asFloat(),
		GameUtils::getKeyOrDefault(initProperties, CameraFocus::MapKeyScrollSpeedY, Value(CameraTrackingData::DefaultCameraFollowSpeed.y)).asFloat()
	);
	this->scrollType = GameUtils::getKeyOrDefault(initProperties, CameraFocus::MapKeyScrollType, Value("")).asString();
}

CameraFocus::~CameraFocus()
{
}

void CameraFocus::onEnter()
{
	super::onEnter();

	CameraTrackingData::CameraScrollType scrollTypeValue = CameraTrackingData::CameraScrollType::Rectangle;

	if (this->scrollType == "ellipse")
	{
		scrollTypeValue = CameraTrackingData::CameraScrollType::Ellipse;
	}

	CameraTrackingData trackingData = CameraTrackingData(this, this->scrollBounds, CameraTrackingData::CameraScrollType::Rectangle, this->scrollSpeed);
	GameCamera::getInstance()->setTarget(trackingData);
}
