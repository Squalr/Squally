#include "SquallyShip.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
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
const float SquallyShip::FlightTimeUntilRedFlame = 4.25f;

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
	this->fireAnimation = SmartAnimationSequenceNode::create();
	this->hasCrashed = false;
	this->flightTime = 0.0f;

	this->ship->setFlippedX(true);
	this->ship->setRotation(-55.0f);
	this->fireAnimation->setFlippedX(true);

	this->ship->addChild(this->fireAnimation);
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
		Vec2(1.0f, 1.0f),
		Vec2(0.0f, 512.0f)
	);

	GameCamera::getInstance()->setTarget(trackingData);

	this->fireAnimation->playAnimationRepeat(ObjectResources::FX_MeteorFireBlue_MeteorFire_0000, 0.025f);

	this->scheduleUpdate();
}

void SquallyShip::initializePositions()
{
	super::initializePositions();

	this->fireAnimation->setPosition(Vec2(112.0f, 32.0f));
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

			squally->setHealth(5);

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
	this->shipCollision->setVelocity(Vec2(-1280.0f, -2048.0f));

	if (this->flightTime < SquallyShip::FlightTimeUntilRedFlame)
	{
		this->flightTime += dt;

		if (this->flightTime >= SquallyShip::FlightTimeUntilRedFlame)
		{
			this->fireAnimation->setPosition(Vec2(112.0f + 44.0f, 32.0f));
			this->fireAnimation->playAnimationRepeat(ObjectResources::FX_MeteorFire_MeteorFire_0000, 0.025f);
		}
	}
}

Vec2 SquallyShip::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void SquallyShip::registerHackables()
{
	super::registerHackables();
}
