#include "Cannon.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Physics/Cannon/CannonBall.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_APPLY_POWER 1

const std::string Cannon::MapKey = "cannon";
const float Cannon::InteractCooldown = 3.0f;
const Vec2 Cannon::LaunchVelocity = Vec2(1400.0f, 1040.0f);

Cannon* Cannon::create(ValueMap& properties)
{
	Cannon* instance = new Cannon(properties);
	
	instance->autorelease();

	return instance;
}

Cannon::Cannon(ValueMap& properties) : super(properties, CSize(320.0f, 224.0f))
{
	this->cannonAnimations = SmartAnimationNode::create(ObjectResources::Traps_Cannon_Animations);
	this->ballAnimationPart = this->cannonAnimations->getAnimationPart("BALL");
	this->shootSound = WorldSound::create(SoundResources::Platformer_FX_Explosions_ExplosionReverb1);
	this->currentMountOffset = Vec2(156.0f, 188.0f);

	float height = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();
	this->cannonAnimations->setPositionY(-height / 2.0f);
	this->cannonAnimations->setScale(1.75f);

	this->frontNode->addChild(this->cannonAnimations);
	this->addChild(this->shootSound);
}

Cannon::~Cannon()
{
}

void Cannon::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
	
	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* skyPortal)
	{
		this->skyPortal = skyPortal;
	}, "sky-portal");

	this->interactionEnabled = false;
	this->currentCooldown = 0.0f;

	this->scheduleUpdate();
}

void Cannon::initializePositions()
{
	super::initializePositions();
}

void Cannon::initializeListeners()
{
	super::initializeListeners();
}

void Cannon::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	if (this->currentCooldown <= 0.0f)
	{
		this->launchCannon();
	}
}

Vec2 Cannon::getReparentPosition(PlatformerEntity* entity)
{
	return this->currentMountOffset;
}

void Cannon::update(float dt)
{
	super::update(dt);

	if (this->currentCooldown > 0.0f)
	{
		this->currentCooldown -= dt;
	}

	if (this->isLaunching)
	{
		this->currentMountOffset += Cannon::LaunchVelocity * dt;
		this->setToMountPosition();
	}
}

void Cannon::returnToIdle()
{
	this->cannonAnimations->clearAnimationPriority();
	this->cannonAnimations->playAnimation();
}

void Cannon::launchCannon()
{
	this->currentCooldown = Cannon::InteractCooldown;
	this->cannonAnimations->clearAnimationPriority();

	this->cannonAnimations->playAnimation("Launch", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(), [=]()
	{
		this->returnToIdle();
	});

	if (this->squally == nullptr || this->skyPortal == nullptr)
	{
		return;
	}

	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		DelayTime::create(0.2f),
		CallFunc::create([=]()
		{
			this->mount(this->squally);
			this->squally->getAnimations()->playAnimation("Launched", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f));
			// this->launchBall();
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->shootSound->play();
			this->isLaunching = true;
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
			Objectives::SetCurrentObjective(ObjectiveKeys::VSExplore);
			this->skyPortal->loadMap();
		}),
		nullptr
	));
}

void Cannon::launchBall()
{
	CannonBall* cannonBall = CannonBall::create(ValueMap(), Cannon::LaunchVelocity);

	this->ballAnimationPart->replaceWithObject(cannonBall, 0.0f, 0.0f);
	cannonBall->setScale(this->cannonAnimations->getScale());
	cannonBall->setRotation(0.0f);

	ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
		this->ballAnimationPart,
		cannonBall,
		SpawnMethod::Above,
		PositionMode::SetToOwner,
		[&]()
		{
		},
		[&]()
		{
			cannonBall = nullptr;
		}
	));
}

