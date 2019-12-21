#include "CameraControl.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string CameraControl::MapKeyCameraControl = "camera-control";
const std::string CameraControl::MapPropertyTarget = "target";

CameraControl* CameraControl::create(ValueMap& properties)
{
	CameraControl* instance = new CameraControl(properties);

	instance->autorelease();

	return instance;
}

CameraControl::CameraControl(ValueMap& properties) : super(properties)
{
	Size controlSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->targetTag = GameUtils::getKeyOrDefault(this->properties, CameraControl::MapPropertyTarget, Value("")).asString();
	this->controlCollision = CollisionObject::create(PhysicsBody::createBox(controlSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->cameraTarget = nullptr;

	this->addChild(this->controlCollision);
}

CameraControl::~CameraControl()
{
}

void CameraControl::initializeListeners()
{
	super::initializeListeners();

	ObjectEvents::watchForObject<CameraTarget>(this, [=](CameraTarget* cameraTarget)
	{
		this->cameraTarget = cameraTarget;
	}, this->targetTag);

	this->controlCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->beginTrack();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->controlCollision->whenStopsCollidingWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->endTrack();

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void CameraControl::beginTrack()
{
	if (this->cameraTarget == nullptr)
	{
		return;
	}

	if (GameCamera::getInstance()->getCurrentTrackingData()->target == this->cameraTarget)
	{
		return;
	}

	GameCamera::getInstance()->pushTarget(this->cameraTarget->getTrackingData());
}

void CameraControl::endTrack()
{
	if (this->cameraTarget == nullptr)
	{
		return;
	}

	if (GameCamera::getInstance()->getCurrentTrackingData()->target == this->cameraTarget)
	{
		GameCamera::getInstance()->popTarget();
	}
}
