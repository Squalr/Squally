#include "SquallyCameraFollowBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/math/CCGeometry.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"

using namespace cocos2d;

const std::string SquallyCameraFollowBehavior::MapKey = "squally-camera-follow";

SquallyCameraFollowBehavior* SquallyCameraFollowBehavior::create(GameObject* owner)
{
	SquallyCameraFollowBehavior* instance = new SquallyCameraFollowBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyCameraFollowBehavior::SquallyCameraFollowBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyCameraFollowBehavior::~SquallyCameraFollowBehavior()
{
}

void SquallyCameraFollowBehavior::onLoad()
{
	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocationPrefix + this->squally->getUniqueIdentifier(), [=](EventCustom* eventCustom)
	{
		CameraTrackingData* data = GameCamera::getInstance()->getCurrentTrackingData();

		if (data != nullptr)
		{
			data->zoom = this->getLayerZoom();
		}
	}));

	// This event fires after squally is relayered properly after loading.
	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventSquallySpawned, [=](EventCustom* eventCustom)
	{
		CameraTrackingData* data = GameCamera::getInstance()->getCurrentTrackingData();

		if (data != nullptr)
		{
			data->zoom = this->getLayerZoom();
		}
	}));
	
	// Request camera & hud track player. Squally may not be in the correct layer yet.
	CameraTrackingData trackingData = CameraTrackingData(
		this->squally,
		Vec2(0.0f, 192.0f),
		Vec2(128.0f, 96.0f),
		CameraTrackingData::CameraScrollType::Rectangle,
		Vec2(0.075f, 0.075f),
		this->getLayerZoom()
	);
	
	GameCamera::getInstance()->setTarget(trackingData, true);
}

void SquallyCameraFollowBehavior::onDisable()
{
	super::onDisable();
}

float SquallyCameraFollowBehavior::getLayerZoom()
{
	MapLayer* layer = GameUtils::GetFirstParentOfType<MapLayer>(this->squally);

	if (layer == nullptr)
	{
		return 1.0f;
	}

	return layer->getPropertyOrDefault(GameObject::MapKeyZoom, Value(1.0f)).asFloat();
}