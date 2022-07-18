#include "WoodenArrow.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

WoodenArrow* WoodenArrow::create()
{
	WoodenArrow* instance = new WoodenArrow();

	instance->autorelease();

	return instance;
}

WoodenArrow::WoodenArrow() : super(nullptr, CollisionObject::createBox(CSize(128.0f, 32.0f)), (int)PlatformerCollisionType::PlayerWeapon, false)
{
	this->sprite = Sprite::create(ItemResources::Equipment_Weapons_Bows_WoodenArrow);

	this->sprite->setRotation(270.0f);

	this->contentNode->addChild(this->sprite);
}

WoodenArrow::~WoodenArrow()
{
}

void WoodenArrow::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}
