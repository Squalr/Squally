#include "CannonBall.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CannonBall::MapKeyCannonBall = "cannon-ball";

CannonBall* CannonBall::create(const ValueMap& properties, Vec2 velocity)
{
	CannonBall* instance = new CannonBall(properties, velocity);
	
	instance->autorelease();

	return instance;
}

CannonBall::CannonBall(const ValueMap& properties, Vec2 velocity) : super(properties)
{
	this->ball = Sprite::create(ObjectResources::Traps_Cannon_BALL);
	this->ballCollision = CollisionObject::create(CollisionObject::createCircle(48.0f), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true));
	this->velocity = velocity;

	this->ballCollision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionData collisionData)
	{
		this->isAccelerating = false;

		return CollisionResult::CollideWithPhysics;
	});

	this->ballCollision->setHorizontalDampening(1.0f);
	//this->ballCollision->setVelocity(this->velocity);

	this->ballCollision->addChild(this->ball);
	this->addChild(this->ballCollision);
}

CannonBall::~CannonBall()
{
}

void CannonBall::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CannonBall::initializePositions()
{
	super::initializePositions();
}

void CannonBall::update(float dt)
{
	super::update(dt);

	if (this->isAccelerating)
	{
		this->ballCollision->setPosition(this->ballCollision->getPosition() + this->velocity * dt);
	}
}

Vec2 CannonBall::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void CannonBall::registerHackables()
{
	super::registerHackables();
}
