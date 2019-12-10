#include "CameraControl.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string CameraControl::MapKeyCameraControl = "camera-control";

CameraControl* CameraControl::create(ValueMap& properties)
{
	CameraControl* instance = new CameraControl(properties);

	instance->autorelease();

	return instance;
}

CameraControl::CameraControl(ValueMap& properties) : super(properties)
{
	Size controlSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());

	this->controlCollision = CollisionObject::create(PhysicsBody::createBox(controlSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);

	this->addChild(this->controlCollision);
}

CameraControl::~CameraControl()
{
}

void CameraControl::initializeListeners()
{
	super::initializeListeners();

	this->controlCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->controlCollision->whenStopsCollidingWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
