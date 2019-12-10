#include "TrackingTarget.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string TrackingTarget::MapKeyTrackingTarget = "camera-control";
const std::string TrackingTarget::MapPropertyZoom = "zoom";

TrackingTarget* TrackingTarget::create(ValueMap& properties)
{
	TrackingTarget* instance = new TrackingTarget(properties);

	instance->autorelease();

	return instance;
}

TrackingTarget::TrackingTarget(ValueMap& properties) : super(properties)
{
	this->zoom = GameUtils::getKeyOrDefault(this->properties, TrackingTarget::MapPropertyZoom, Value(0.0f)).asFloat();
	this->debugDraw = DrawNode::create();
	Size size = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(32.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(32.0f)).asFloat()
	);

	this->debugDraw->drawSolidRect(-Vec2(size / 2.0f), Vec2(size / 2.0f), Color4F::GREEN);

	this->addChild(this->debugDraw);
}

TrackingTarget::~TrackingTarget()
{
}

void TrackingTarget::onEnter()
{
	super::onEnter();
}

void TrackingTarget::onDeveloperModeEnable()
{
	this->debugDraw->setVisible(true);
}

void TrackingTarget::onDeveloperModeDisable()
{
	this->debugDraw->setVisible(false);
}
