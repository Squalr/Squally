#include "CameraFocus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CameraFocus::MapKeyCameraFocus = "camera-focus";
const std::string CameraFocus::MapKeyZoom = "zoom";
const std::string CameraFocus::MapKeyScrollBoundsX = "scroll-bounds-x";
const std::string CameraFocus::MapKeyScrollBoundsY = "scroll-bounds-y";
const std::string CameraFocus::MapKeyScrollSpeedX = "scroll-speed-x";
const std::string CameraFocus::MapKeyScrollSpeedY = "scroll-speed-y";
const std::string CameraFocus::MapKeyScrollType = "scroll-type";

CameraFocus* CameraFocus::create(ValueMap& properties)
{
	CameraFocus* instance = new CameraFocus(properties);

	instance->autorelease();

	return instance;
}

CameraFocus::CameraFocus(ValueMap& properties) : super(properties)
{
	this->zoom = GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyZoom, Value(1.0f)).asFloat();
	this->scrollBounds = Vec2(
		GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyScrollBoundsX, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyScrollBoundsY, Value(0.0f)).asFloat()
	);
	this->scrollSpeed = Vec2(
		GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyScrollSpeedX, Value(CameraTrackingData::DefaultCameraFollowSpeed.x)).asFloat(),
		GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyScrollSpeedY, Value(CameraTrackingData::DefaultCameraFollowSpeed.y)).asFloat()
	);
	this->scrollType = GameUtils::getKeyOrDefault(properties, CameraFocus::MapKeyScrollType, Value("")).asString();
}

CameraFocus::~CameraFocus()
{
}

void CameraFocus::onEnter()
{
	super::onEnter();
}

void CameraFocus::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	CameraTrackingData::CameraScrollType scrollTypeValue = CameraTrackingData::CameraScrollType::Rectangle;

	if (this->scrollType == "ellipse")
	{
		scrollTypeValue = CameraTrackingData::CameraScrollType::Ellipse;
	}

	CameraTrackingData trackingData = CameraTrackingData(
		this,
		Vec2::ZERO,
		this->scrollBounds,
		scrollTypeValue,
		this->scrollSpeed,
		this->zoom
	);

	GameCamera::getInstance()->setTarget(trackingData);
	GameCamera::getInstance()->setCameraPositionToTrackedTarget();
}
