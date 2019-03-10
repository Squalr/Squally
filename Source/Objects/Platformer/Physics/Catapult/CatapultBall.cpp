#include "CatapultBall.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CatapultBall::MapKeyCatapultBall = "catapult-ball";

CatapultBall* CatapultBall::create(const ValueMap& initProperties, Vec2 velocity)
{
	CatapultBall* instance = new CatapultBall(initProperties, velocity);
	
	instance->autorelease();

	return instance;
}

CatapultBall::CatapultBall(const ValueMap& initProperties, Vec2 velocity) : HackableObject(initProperties)
{
	this->ball = Sprite::create(ObjectResources::War_Machines_Catapult_BALL);
	this->ballCollision = CollisionObject::create(PhysicsBody::createCircle(48.0f), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->velocity = velocity;
	this->isAccelerating = true;

	this->ballCollision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		this->isAccelerating = false;

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->ballCollision->setHorizontalDampening(1.0f);
	//this->ballCollision->setVelocity(this->velocity);

	this->ballCollision->addChild(this->ball);
	this->addChild(this->ballCollision);
}

CatapultBall::~CatapultBall()
{
}

void CatapultBall::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CatapultBall::initializePositions()
{
	super::initializePositions();
}

void CatapultBall::update(float dt)
{
	super::update(dt);

	if (this->isAccelerating)
	{
		this->ballCollision->setPosition(this->ballCollision->getPosition() + this->velocity * dt);
	}

	// TODO: God damn it, gravity seems too slow. This is a more fundamental issue that needs patching elsewhere.
	// Also we can't do this when colliding because we'll just slide through the ground with ease
	if (this->ballCollision->getCurrentCollisions().empty())
	{
		this->ballCollision->setPositionY(this->ballCollision->getPosition().y - 420.0f * dt);
	}
}

Vec2 CatapultBall::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void CatapultBall::registerHackables()
{
	super::registerHackables();
}
