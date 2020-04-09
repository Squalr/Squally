#include "FloatingBomb.h"

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

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string FloatingBomb::MapKey = "floating-bomb";

FloatingBomb* FloatingBomb::create(ValueMap& properties)
{
	FloatingBomb* instance = new FloatingBomb(properties);
	
	instance->autorelease();

	return instance;
}

FloatingBomb::FloatingBomb(ValueMap& properties) : super(properties)
{
	this->bomb = Sprite::create(ObjectResources::Traps_FloatingBomb_FloatingBomb);
	this->bombCollision = CollisionObject::create(CollisionObject::createCircle(128.0f), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(true, true));

	this->bombCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->bombCollision->addChild(this->bomb);
	this->addChild(this->bombCollision);
}

FloatingBomb::~FloatingBomb()
{
}

void FloatingBomb::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void FloatingBomb::initializePositions()
{
	super::initializePositions();
}

void FloatingBomb::update(float dt)
{
	super::update(dt);
}

Vec2 FloatingBomb::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void FloatingBomb::registerHackables()
{
	super::registerHackables();
}
