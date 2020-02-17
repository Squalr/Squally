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

WoodenCrate* WoodenCrate::create(ValueMap& properties)
{
	WoodenCrate* instance = new WoodenCrate(properties);
	
	instance->autorelease();

	return instance;
}

WoodenCrate::WoodenCrate(ValueMap& properties) : super(properties)
{
	this->box = Sprite::create(ObjectResources::Physics_WoodenCrate_WoodenCrate);
	this->boxCollision = CollisionObject::create(CollisionObject::createBox(Size(160.0f, 154.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true));

	this->boxCollision->addChild(this->box);
	this->addChild(this->boxCollision);
}

WoodenCrate::~WoodenCrate()
{
}

void WoodenCrate::initializeListeners()
{
	super::initializeListeners();

	this->boxCollision->whileCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

Vec2 WoodenCrate::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void WoodenCrate::registerHackables()
{
	super::registerHackables();
}
