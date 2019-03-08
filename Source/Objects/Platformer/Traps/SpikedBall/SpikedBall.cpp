#include "SpikedBall.h"

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

#define LOCAL_FUNC_ID_SWING 1

const std::string SpikedBall::MapKeySpikedBall = "spiked-ball";

SpikedBall* SpikedBall::create(ValueMap& initProperties)
{
	SpikedBall* instance = new SpikedBall(initProperties);
	
	instance->autorelease();

	return instance;
}

SpikedBall::SpikedBall(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->ball = Sprite::create(ObjectResources::Traps_SpikeBall_SpikeBall);
	this->ballCollision = CollisionObject::create(PhysicsBody::createCircle(80.0f), (CollisionType)PlatformerCollisionType::Damage, false, false);

	this->ballCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->ballCollision->addChild(this->ball);
	this->addChild(this->ballCollision);
}

SpikedBall::~SpikedBall()
{
}

void SpikedBall::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpikedBall::initializePositions()
{
	super::initializePositions();
}

void SpikedBall::update(float dt)
{
	super::update(dt);
}

Vec2 SpikedBall::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void SpikedBall::registerHackables()
{
	super::registerHackables();
}
