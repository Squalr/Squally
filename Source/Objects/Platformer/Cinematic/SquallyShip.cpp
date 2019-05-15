#include "SquallyShip.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/SwitchEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyShip::MapKeySquallyShip = "squally-ship";

SquallyShip* SquallyShip::create(ValueMap& initProperties)
{
	SquallyShip* instance = new SquallyShip(initProperties);

	instance->autorelease();

	return instance;
}

SquallyShip::SquallyShip(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->ship = Sprite::create(ObjectResources::Cinematic_SpaceShipSqually);
	this->shipCollision = CollisionObject::create(PhysicsBody::createBox(Size(320.0f, 224.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->hasCrashed = false;

	this->shipCollision->setRotation(45.0f);

	this->shipCollision->addChild(this->ship);
	this->addChild(this->shipCollision);
}

SquallyShip::~SquallyShip()
{
}

void SquallyShip::onEnter()
{
	super::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(
		this->ship,
		Vec2(0.0f, 0.0f),
		CameraTrackingData::CameraScrollType::Rectangle,
		Vec2(0.575f, 0.575f)
	);

	GameCamera::getInstance()->setTarget(trackingData);

	this->scheduleUpdate();
}

void SquallyShip::initializePositions()
{
	super::initializePositions();
}

void SquallyShip::initializeListeners()
{
	super::initializeListeners();

	this->shipCollision->whenCollidesWith({(int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics}, [=](CollisionObject::CollisionData data)
	{
		if (!this->hasCrashed)
		{
			this->hasCrashed = true;

			GameCamera::getInstance()->clearTargets();

			Squally* squally = Squally::deserialize(this->properties);

			ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(this->ship, squally, ObjectEvents::SpawnMethod::Above));

			squally->getEntityCollision()->setPosition(GameUtils::getWorldCoords(this->shipCollision) + Vec2(0.0f, 128.0f));

			this->shipCollision->setPhysicsEnabled(false);
			this->setVisible(false);
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

void SquallyShip::update(float dt)
{
	this->shipCollision->setVelocity(Vec2(1280.0f, -1280.0f));
}

Vec2 SquallyShip::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void SquallyShip::registerHackables()
{
	super::registerHackables();
}
