#include "CameraTarget.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CameraTarget::MapKeyCameraTarget = "camera-target";
const std::string CameraTarget::MapPropertyZoom = "zoom";

CameraTarget* CameraTarget::create(ValueMap& properties)
{
	CameraTarget* instance = new CameraTarget(properties);

	instance->autorelease();

	return instance;
}

CameraTarget::CameraTarget(ValueMap& properties) : super(properties)
{
	this->zoom = GameUtils::getKeyOrDefault(this->properties, CameraTarget::MapPropertyZoom, Value(1.0f)).asFloat();
	this->debugDraw = DrawNode::create();
	Size size = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(32.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(32.0f)).asFloat()
	);

	this->debugDraw->drawSolidRect(-Vec2(size / 2.0f), Vec2(size / 2.0f), Color4F::GREEN);

	this->addChild(this->debugDraw);
}

CameraTarget::~CameraTarget()
{
}

void CameraTarget::onEnter()
{
	super::onEnter();
}

void CameraTarget::onDeveloperModeEnable(int debugLevel)
{
	this->debugDraw->setVisible(true);
}

void CameraTarget::onDeveloperModeDisable()
{
	this->debugDraw->setVisible(false);
}

CameraTrackingData CameraTarget::getTrackingData()
{
	return CameraTrackingData(
		this,
		Vec2::ZERO,
		CameraTrackingData::DefaultCameraOffset,
		CameraTrackingData::CameraScrollType::Rectangle,
		cocos2d::Vec2(0.015f, 0.015f),
		this->zoom
	);
}
