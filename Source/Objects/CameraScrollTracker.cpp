#include "CameraScrollTracker.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

const std::string CameraScrollTracker::MapKeyCameraScrollTracker = "camera-scroll-tracker";
const std::string CameraScrollTracker::MapKeyZoom = "zoom";
const std::string CameraScrollTracker::MapKeyScrollBoundsX = "scroll-bounds-x";
const std::string CameraScrollTracker::MapKeyScrollBoundsY = "scroll-bounds-y";
const std::string CameraScrollTracker::MapKeyScrollSpeedX = "scroll-speed-x";
const std::string CameraScrollTracker::MapKeyScrollSpeedY = "scroll-speed-y";
const std::string CameraScrollTracker::MapKeyScrollType = "scroll-type";
const float CameraScrollTracker::ScrollSpeed = -64.0f;

CameraScrollTracker* CameraScrollTracker::create(ValueMap& initProperties)
{
	CameraScrollTracker* instance = new CameraScrollTracker(initProperties);

	instance->autorelease();

	return instance;
}

CameraScrollTracker::CameraScrollTracker(ValueMap& initProperties) : SerializableObject(initProperties)
{
	this->zoom = GameUtils::getKeyOrDefault(initProperties, CameraScrollTracker::MapKeyZoom, Value(1.0f)).asFloat();
	this->trackTarget = Node::create();
	this->hud = Hud::create();
	this->scrollDistance = 0.0f;

	Sprite* debug = Sprite::create(HexusResources::Menus_WoodBackground);

	debug->setScale(20.0f);

	this->hud->addChild(debug);

	if (this->polylinePoints.size() >= 2)
	{
		this->source = this->polylinePoints[0];
		this->dest = this->polylinePoints[1];
	}
	else
	{
		this->source = Vec2::ZERO;
		this->dest = Vec2::ZERO;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->addChild(this->trackTarget);
	this->addChild(this->hud);
}

CameraScrollTracker::~CameraScrollTracker()
{
}

void CameraScrollTracker::onEnter()
{
	super::onEnter();
}

void CameraScrollTracker::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	CameraTrackingData trackingData = CameraTrackingData(
		this->trackTarget,
		CameraTrackingData::DefaultCameraOffset,
		CameraTrackingData::CameraScrollType::Rectangle,
		CameraTrackingData::DefaultCameraFollowSpeed,
		Vec2::ZERO,
		this->zoom
	);

	GameCamera::getInstance()->setTarget(trackingData);

	this->scrollBy(0.0f);
}

void CameraScrollTracker::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(MouseEvents::EventMouseScroll, [=](EventCustom* eventCustom)
	{
		MouseEvents::MouseEventArgs* args = static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->scrollBy(args->scrollDelta.y * CameraScrollTracker::ScrollSpeed);
		}
	}));
}

void CameraScrollTracker::scrollBy(float delta)
{
	float totalDistance = this->dest.distance(this->source);
	Vec2 unit = (source - dest) / totalDistance;

	this->scrollDistance = MathUtils::clamp(this->scrollDistance + delta, 0.0f, totalDistance);
	this->trackTarget->setPosition(this->source + unit * this->scrollDistance);
}