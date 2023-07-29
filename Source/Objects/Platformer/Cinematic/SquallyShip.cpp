#include "SquallyShip.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/HackableEvents.h"
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
#include "Events/PlatformerEvents.h"
#include "Events/SwitchEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/SquallyBehaviorGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
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

SquallyShip::SquallyShip(ValueMap& properties) : super(properties, CSize(320.0f, 224.0f), false)
{
	this->lightningStrike = SmartAnimationSequenceNode::create();
	this->shipContainer = Node::create();
	this->ship = Sprite::create(ObjectResources::Cinematic_SpaceShipSqually);
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
		InputEvents::KeyCode::KEY_S,
		InputEvents::KeyCode::KEY_W,
		InputEvents::KeyCode::KEY_A,
		InputEvents::KeyCode::KEY_G,
		InputEvents::KeyCode::KEY_L,
		InputEvents::KeyCode::KEY_O,
		InputEvents::KeyCode::KEY_R,
		InputEvents::KeyCode::KEY_D,
	}, [=]()
	{
		this->onCrash();
	});

	this->ship->setFlippedX(true);
	this->fireAnimation->setFlippedX(true);
	this->thrustAnimation->setFlippedX(true);

	this->fireAnimation->addChild(this->fireSound);
	this->ship->addChild(this->fireRingAnimation);
	this->ship->addChild(this->fireAnimation);
	this->ship->addChild(this->thrustAnimation);
	this->ship->addChild(this->lightningSound);
	this->ship->addChild(this->thrusterSound);
	this->ship->addChild(this->enterAtmosphereSound);
	this->ship->addChild(this->crashSound);
	this->shipContainer->addChild(this->lightningStrike);
	this->shipContainer->addChild(this->explodeAnimation);
	this->shipContainer->addChild(this->groundFireAnimation);
	this->shipContainer->addChild(this->groundFireSmallAnimation);
	this->shipContainer->addChild(this->shipFireAnimation);
	this->shipContainer->addChild(this->smokeAnimation);
	this->shipContainer->addChild(this->ship);
	this->frontNode->addChild(this->shipContainer);
	this->addChild(this->skipSequence);
}

SquallyShip::~SquallyShip()
{
}

void SquallyShip::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySquallyCrashed, Value(false)).asBool())
		{
			this->runShipSequence();
		}

	}, Squally::MapKey);

	this->disable();
}

void SquallyShip::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void SquallyShip::update(float dt)
{
	super::update(dt);

	if (this->isFalling && !this->hasCrashed)
	{
		static const Vec2 FallSpeed = Vec2(-512.0f, -512.0f);

		this->setPosition(this->getPosition() + FallSpeed * dt);
	}
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

	const float FireOffsetY = 0.0f;
	this->groundFireAnimation->setPosition(Vec2(-48.0f, FireOffsetY));
	this->groundFireSmallAnimation->setPosition(Vec2(80.0f, FireOffsetY - 8.0f));
}

void SquallyShip::initializeListeners()
{
	super::initializeListeners();

	this->interactCollision->whenCollidesWith({(int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics}, [=](CollisionData data)
	{
		this->onCrash();

		return CollisionResult::CollideWithPhysics;
	});
}

Vec2 SquallyShip::getReparentPosition(PlatformerEntity* entity)
{
	return Vec2(0.0f, -56.0f);
}

void SquallyShip::runShipSequence()
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			HackableEvents::TriggerDisallowHackerMode();
			this->mount(this->squally);
			this->setMountDirection(MountBase::MountDirection::Left);
			this->faceEntityTowardsDirection();
			PlatformerEvents::TriggerCinematicHijack();
			this->defer([=]()
			{
				GameCamera::getInstance()->setCameraPositionToTrackedTarget();
				this->originalFollowSpeed = GameCamera::getInstance()->getCurrentTrackingData()->followSpeed;
				GameCamera::getInstance()->getCurrentTrackingData()->followSpeed *= 2.5f;
			});
			this->thrusterSound->play(true);
			this->thrustAnimation->playAnimationRepeat(FXResources::SmokeFlameTrail_SmokeFlameTrail_0000, 0.05f);
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			this->lightningStrike->playAnimation(FXResources::Lightning_Lightning_0000, 0.06f);
			this->lightningSound->play();
			
			AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");
			
			// Hacky way to show worried expression
			if (mouth != nullptr)
			{
				mouth->setRotation(180.0f);
				mouth->setOffset(Vec2(-34.0f, 16.0f));
			}
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->isFalling = true;
			this->rootNode->runAction(EaseSineIn::create(RotateTo::create(1.0f, -45.0f)));
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

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			// Force hacker mode enable for cinematic
			HackableEvents::TriggerAllowHackerMode();
			HackableEvents::TriggerHackerModeEnable(HackToggleArgs());
			PlatformerEvents::TriggerCinematicRestore();
			HackableEvents::TriggerDisallowHackerMode();
		}),
		DelayTime::create(0.1f),
		CallFunc::create([=]()
		{
			AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");

			if (mouth != nullptr)
			{
				mouth->reattachToTimeline();
				mouth->setOffset(Vec2::ZERO);
			}

			this->dismountAll();
			this->hasCrashed = true;

			GameCamera::getInstance()->getCurrentTrackingData()->followSpeed = this->originalFollowSpeed;
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyCrashed, Value(true));
			SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
			SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
			SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
			SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyLayerId);

			squally->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->setHealth(1);
			});

			this->rootNode->setRotation(0.0f);
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
			HackableEvents::TriggerAllowHackerMode();
		}),
		nullptr
	));
}
