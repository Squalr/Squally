#include "Catapult.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/SpawnEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Physics/Catapult/CatapultBall.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GET_POWER 1

const std::string Catapult::MapKeyCatapult = "catapult";
const float Catapult::InteractCooldown = 3.0f;

Catapult* Catapult::create(ValueMap& initProperties)
{
	Catapult* instance = new Catapult(initProperties);
	
	instance->autorelease();

	return instance;
}

Catapult::Catapult(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->catapultAnimations = SmartAnimationNode::create(ObjectResources::War_Machines_Catapult_Animations);
	this->catapultCollision = CollisionObject::create(PhysicsBody::createBox(Size(512.0f, 320.0f)), (CollisionType)PlatformerCollisionType::Physics, false, false);
	this->ballAnimationPart = this->catapultAnimations->getAnimationPart("BALL");

	this->interactionEnabled = false;
	this->currentCooldown = 0.0f;
	float height = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyHeight, Value(0.0f)).asFloat();
	this->catapultAnimations->setPositionY(-height / 2.0f);
	this->catapultAnimations->setScale(1.75f);

	this->catapultCollision->addChild(this->catapultAnimations);
	this->addChild(this->catapultCollision);
}

Catapult::~Catapult()
{
}

void Catapult::onEnter()
{
	super::onEnter();

	this->interactionEnabled = false;
	this->currentCooldown = 0.0f;

	this->scheduleUpdate();
}

void Catapult::initializePositions()
{
	super::initializePositions();
}

void Catapult::initializeListeners()
{
	super::initializeListeners();

	this->catapultCollision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->catapultCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->interactionEnabled = true;

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->catapultCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->interactionEnabled = false;

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Catapult::update(float dt)
{
	super::update(dt);

	if (this->currentCooldown > 0.0f)
	{
		this->currentCooldown -= dt;
	}

	if (this->interactionEnabled && this->currentCooldown <= 0.0f)
	{
		if (Input::isKeyJustPressed(EventKeyboard::KeyCode::KEY_V))
		{
			this->currentCooldown = Catapult::InteractCooldown;
			this->catapultAnimations->playAnimation("Launch");

			this->runAction(Sequence::create(
				DelayTime::create(0.8f),
				CallFunc::create([=]()
				{
					CatapultBall* catapultBall = CatapultBall::create(ValueMap());

					this->ballAnimationPart->replaceWithObject(catapultBall, 0.0f, 0.0f);
					catapultBall->setScale(this->catapultAnimations->getScale());

					SpawnEvents::TriggerObjectSpawn(SpawnEvents::RequestObjectSpawnArgs(
						this->ballAnimationPart,
						catapultBall,
						SpawnEvents::SpawnMethod::Above
					));
				}),
				nullptr
			));
		}
	}
}

Vec2 Catapult::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Catapult::registerHackables()
{
	super::registerHackables();
}
