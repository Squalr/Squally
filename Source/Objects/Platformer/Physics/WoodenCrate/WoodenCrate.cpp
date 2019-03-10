#include "WoodenCrate.h"

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

const std::string WoodenCrate::MapKeyWoodenCrate = "wooden-crate";

WoodenCrate* WoodenCrate::create(ValueMap& initProperties)
{
	WoodenCrate* instance = new WoodenCrate(initProperties);
	
	instance->autorelease();

	return instance;
}

WoodenCrate::WoodenCrate(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->box = Sprite::create(ObjectResources::Physics_WoodenCrate_WoodenCrate);
	this->boxCollision = CollisionObject::create(PhysicsBody::createBox(Size(160.0f, 160.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);

	this->boxCollision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->boxCollision->addChild(this->box);
	this->addChild(this->boxCollision);
}

WoodenCrate::~WoodenCrate()
{
}

void WoodenCrate::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void WoodenCrate::initializePositions()
{
	super::initializePositions();
}

void WoodenCrate::update(float dt)
{
	super::update(dt);
}

Vec2 WoodenCrate::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void WoodenCrate::registerHackables()
{
	super::registerHackables();
}
