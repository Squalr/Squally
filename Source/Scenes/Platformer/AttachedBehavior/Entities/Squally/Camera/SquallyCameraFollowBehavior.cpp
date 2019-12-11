#include "SquallyCameraFollowBehavior.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;

const std::string SquallyCameraFollowBehavior::MapKeyAttachedBehavior = "squally-camera-follow";

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
	// Request camera & hud track player
	CameraTrackingData trackingData = CameraTrackingData(
		this->squally,
		Vec2(0.0f, 128.0f),
		Vec2(128.0f, 96.0f),
		CameraTrackingData::CameraScrollType::Ellipse,
		Vec2(0.075f, 0.075f)
	);
	
	GameCamera::getInstance()->setTarget(trackingData, true);
}
