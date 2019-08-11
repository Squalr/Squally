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
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/SwitchEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/SquallyBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyHealthBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
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

SquallyShip::SquallyShip(ValueMap& initProperties) : super(initProperties)
{
	this->ship = Sprite::create(ObjectResources::Cinematic_SpaceShipSqually);
	this->shipCollision = CollisionObject::create(PhysicsBody::createBox(Size(320.0f, 224.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->shipFireAnimation = SmartAnimationSequenceNode::create();
	this->smokeAnimation = SmartAnimationSequenceNode::create();
	this->fireAnimation = SmartAnimationSequenceNode::create();
	this->thrustAnimation = SmartAnimationSequenceNode::create();
	this->explodeAnimation = SmartAnimationSequenceNode::create();
	this->fireRingAnimation = SmartAnimationSequenceNode::create();
	this->groundFireAnimation = SmartAnimationSequenceNode::create();
	this->groundFireSmallAnimation = SmartAnimationSequenceNode::create();
	this->thrusterSound = Sound::create(SoundResources::Platformer_Objects_LowFlame);
	this->enterAtmosphereSound = Sound::create(SoundResources::Platformer_Objects_WooshRough);
	this->crashSound = Sound::create(SoundResources::Platformer_Objects_Crash);
	this->fireSound = Sound::create(SoundResources::Platformer_Environment_Fire);
	this->hasCrashed = false;
	this->flightTime = 0.0f;

	this->smokeAnimation->setRotation(-45.0f);
	this->shipFireAnimation->setRotation(-45.0f);
	this->ship->setFlippedX(true);
	this->ship->setRotation(-45.0f);
	this->fireAnimation->setFlippedX(true);
	this->thrustAnimation->setFlippedX(true);
	this->fireSound->toggleCameraDistanceFade(true);

	this->fireAnimation->addChild(this->fireSound);
	this->ship->addChild(this->fireRingAnimation);
	this->ship->addChild(this->fireAnimation);
	this->ship->addChild(this->thrustAnimation);
	this->shipCollision->addChild(this->shipFireAnimation);
	this->shipCollision->addChild(this->smokeAnimation);
	this->shipCollision->addChild(this->ship);
	this->shipCollision->addChild(this->explodeAnimation);
	this->shipCollision->addChild(this->groundFireAnimation);
	this->shipCollision->addChild(this->groundFireSmallAnimation);
	this->addChild(this->shipCollision);
	this->addChild(this->thrusterSound);
	this->addChild(this->enterAtmosphereSound);
	this->addChild(this->crashSound);
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

	this->smokeAnimation->playAnimationRepeat(FXResources::SmokeWhisp_SmokeWhisp_0000, 0.06f);
	this->shipFireAnimation->playAnimationRepeat(FXResources::FlameWhisp_FlameWhisp_0000, 0.065f, 1.25f, true);
	this->fireAnimation->playAnimationRepeat(FXResources::MeteorFireBlue_MeteorFire_0000, 0.06f);
	this->thrustAnimation->playAnimationRepeat(FXResources::SmokeFlameTrail_SmokeFlameTrail_0000, 0.05f);
	this->thrusterSound->play(true);

	this->scheduleUpdate();
}

void SquallyShip::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	GameCamera::getInstance()->setCameraZoom(2.0f);
}

void SquallyShip::initializePositions()
{
	super::initializePositions();

	this->smokeAnimation->setPosition(Vec2(-64.0f, -64.0f));
	this->shipFireAnimation->setPosition(Vec2(-32.0f, -32.0f));
	this->fireAnimation->setPosition(Vec2(112.0f, 32.0f));
	this->fireRingAnimation->setPosition(Vec2(0.0f, 32.0f));
	this->thrustAnimation->setPosition(Vec2(448.0f, 52.0f));
	this->groundFireAnimation->setPosition(Vec2(-48.0f, -48.0f));
	this->groundFireSmallAnimation->setPosition(Vec2(80.0f, -56.0f));
}

void SquallyShip::initializeListeners()
{
	super::initializeListeners();

	this->shipCollision->whenCollidesWith({(int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics}, [=](CollisionObject::CollisionData data)
	{
		if (!this->hasCrashed)
		{
			this->hasCrashed = true;

			Vec2 cameraCoords = GameCamera::getInstance()->getCameraPosition();
			Vec2 crashCoords = GameUtils::getWorldCoords(this->shipCollision);
			Squally* squally = Squally::deserialize(this->properties);
			SquallyBehaviorGroup* squallyBehavior = SquallyBehaviorGroup::create(squally, "");
			SquallyHealthBehavior* health = squally->getAttachedBehavior<SquallyHealthBehavior>();
			
			health->setHealth(1);

			ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
				this->ship,
				squally,
				ObjectEvents::SpawnMethod::Above,
				ObjectEvents::PositionMode::Discard
			));

			squally->setPosition(crashCoords);
			squally->attachBehavior(squallyBehavior);
			GameCamera::getInstance()->setCameraPosition(cameraCoords);

			this->shipCollision->setPhysicsEnabled(false);
			this->ship->setVisible(false);
			
			this->smokeAnimation->stopAnimation();
			this->shipFireAnimation->stopAnimation();
			this->fireAnimation->stopAnimation();
			this->thrustAnimation->stopAnimation();
			this->explodeAnimation->playAnimation(FXResources::ExplosionGround_ExplosionGround_0000, 0.05f, true);
			this->groundFireAnimation->playAnimationRepeat(FXResources::FlameBig_FlameBig_0000, 0.05f);
			this->groundFireSmallAnimation->playAnimationRepeat(FXResources::FlameSmall_FlameSmall_0000, 0.05f);

			this->thrusterSound->stop();
			this->crashSound->play();
			this->fireSound->play(true);
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

void SquallyShip::update(float dt)
{
	this->shipCollision->setVelocity(Vec2(-2048.0f, -2048.0f));

	if (this->flightTime < SquallyShip::FlightTimeUntilRedFlame)
	{
		this->flightTime += dt;

		if (this->flightTime >= SquallyShip::FlightTimeUntilRedFlame)
		{
			this->fireAnimation->setPosition(Vec2(112.0f + 44.0f, 32.0f));
			this->fireAnimation->playAnimationRepeat(FXResources::MeteorFire_MeteorFire_0000, 0.06f);
			this->fireRingAnimation->playAnimation(FXResources::FireRing_FireRing_0000, 0.08f, true);

			this->enterAtmosphereSound->play();
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
