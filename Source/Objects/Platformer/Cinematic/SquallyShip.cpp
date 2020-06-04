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
#include "Engine/Konami/KSequence.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/SwitchEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/SquallyBehaviorGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyShip::MapKey = "squally-ship";

SquallyShip* SquallyShip::create(ValueMap& properties)
{
	SquallyShip* instance = new SquallyShip(properties);

	instance->autorelease();

	return instance;
}

SquallyShip::SquallyShip(ValueMap& properties) : super(properties)
{
	this->lightningStrike = SmartAnimationSequenceNode::create();
	this->shipContainer = Node::create();
	this->ship = Sprite::create(ObjectResources::Cinematic_SpaceShipSqually);
	this->shipCollision = CollisionObject::create(CollisionObject::createBox(Size(320.0f, 224.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true));
	this->shipFireAnimation = SmartAnimationSequenceNode::create();
	this->smokeAnimation = SmartAnimationSequenceNode::create();
	this->fireAnimation = SmartAnimationSequenceNode::create();
	this->thrustAnimation = SmartAnimationSequenceNode::create();
	this->explodeAnimation = SmartAnimationSequenceNode::create();
	this->fireRingAnimation = SmartAnimationSequenceNode::create();
	this->groundFireAnimation = SmartAnimationSequenceNode::create();
	this->groundFireSmallAnimation = SmartAnimationSequenceNode::create();
	this->lightningSound = Sound::create(SoundResources::Hexus_Attacks_Energy);
	this->thrusterSound = Sound::create(SoundResources::Platformer_FX_Fire_LowFlame1);
	this->enterAtmosphereSound = Sound::create(SoundResources::Platformer_FX_Woosh_WooshBurning1);
	this->crashSound = Sound::create(SoundResources::Platformer_FX_Explosions_Crash1);
	this->fireSound = WorldSound::create(SoundResources::Platformer_FX_Fire_Fire1);
	this->hasCrashed = false;
	this->flightTime = 0.0f;

	this->skipSequence = KSequence::create(
	{
		EventKeyboard::KeyCode::KEY_S,
		EventKeyboard::KeyCode::KEY_W,
		EventKeyboard::KeyCode::KEY_A,
		EventKeyboard::KeyCode::KEY_G,
		EventKeyboard::KeyCode::KEY_L,
		EventKeyboard::KeyCode::KEY_O,
		EventKeyboard::KeyCode::KEY_R,
		EventKeyboard::KeyCode::KEY_D,
	}, [=]()
	{
		this->onCrash();
	});

	this->ship->setFlippedX(true);
	this->fireAnimation->setFlippedX(true);
	this->thrustAnimation->setFlippedX(true);
	this->shipCollision->setGravityEnabled(false);

	this->fireAnimation->addChild(this->fireSound);
	this->ship->addChild(this->fireRingAnimation);
	this->ship->addChild(this->fireAnimation);
	this->ship->addChild(this->thrustAnimation);
	this->ship->addChild(this->lightningSound);
	this->ship->addChild(this->thrusterSound);
	this->ship->addChild(this->enterAtmosphereSound);
	this->ship->addChild(this->crashSound);
	this->shipContainer->addChild(this->shipFireAnimation);
	this->shipContainer->addChild(this->smokeAnimation);
	this->shipContainer->addChild(this->ship);
	this->shipCollision->addChild(this->lightningStrike);
	this->shipCollision->addChild(this->explodeAnimation);
	this->shipCollision->addChild(this->groundFireAnimation);
	this->shipCollision->addChild(this->groundFireSmallAnimation);
	this->shipCollision->addChild(this->shipContainer);
	this->addChild(this->shipCollision);
	this->addChild(this->skipSequence);
}

SquallyShip::~SquallyShip()
{
}

void SquallyShip::onEnter()
{
	super::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(
		this->shipCollision,
		Vec2(0.0f, 128.0f),
		Vec2(0.0f, 0.0f),
		CameraTrackingData::CameraScrollType::Rectangle,
		Vec2(1.0f, 1.0f)
	);

	GameCamera::getInstance()->setTarget(trackingData);

	this->runShipSequence();
}

void SquallyShip::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	GameCamera::getInstance()->setCameraZoom(2.0f);
}

void SquallyShip::initializePositions()
{
	super::initializePositions();

	this->lightningStrike->setPosition(Vec2(-32.0f, 420.0f));
	this->smokeAnimation->setPosition(Vec2(-64.0f, 16.0f));
	this->shipFireAnimation->setPosition(Vec2(-64.0f, 48.0f));
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
		this->onCrash();

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

Vec2 SquallyShip::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void SquallyShip::registerHackables()
{
	super::registerHackables();
}

void SquallyShip::runShipSequence()
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->shipCollision->setVelocity(Vec2(0.0f, 0.0f));
			this->shipCollision->setHorizontalDampening(1.0f);
			this->shipCollision->setVerticalDampening(1.0f);
			this->thrusterSound->play(true);
			this->thrustAnimation->playAnimationRepeat(FXResources::SmokeFlameTrail_SmokeFlameTrail_0000, 0.05f);
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			this->lightningStrike->playAnimation(FXResources::Lightning_Lightning_0000, 0.06f);
			this->lightningSound->play();
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->shipCollision->setVelocity(Vec2(-2048.0f, -512.0f));
			this->shipContainer->runAction(EaseSineIn::create(RotateTo::create(2.0f, -45.0f)));
			this->smokeAnimation->playAnimationRepeat(FXResources::SmokeWhisp_SmokeWhisp_0000, 0.06f);
			this->shipFireAnimation->playAnimationRepeat(FXResources::FlameWhisp_FlameWhisp_0000, 0.065f, 1.25f, true);
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->fireAnimation->playAnimationRepeat(FXResources::MeteorFireBlue_MeteorFire_0000, 0.06f);
		}),
		DelayTime::create(3.0f),
		CallFunc::create([=]()
		{
			this->fireAnimation->setPosition(Vec2(112.0f + 44.0f, 32.0f));
			this->fireAnimation->playAnimationRepeat(FXResources::MeteorFire_MeteorFire_0000, 0.06f);
			this->fireRingAnimation->playAnimation(FXResources::FireRing_FireRing_0000, 0.08f, true);

			this->enterAtmosphereSound->play();
		}),
		nullptr
	));
}

void SquallyShip::onCrash()
{
	if (this->hasCrashed)
	{
		return;
	}

	this->hasCrashed = true;

	Vec2 cameraCoords = GameCamera::getInstance()->getCameraPosition();
	Vec2 crashCoords = GameUtils::getWorldCoords(this->shipCollision);
	Squally* squally = Squally::create();
	
	SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
	SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
	SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
	SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyLayerId);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		this->ship,
		squally,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
			squally->setPosition(crashCoords);
			squally->attachBehavior(SquallyBehaviorGroup::create(squally));

			squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->setHealth(1);
			});
		},
		[&]()
		{
			squally = nullptr;
		}
	));

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
