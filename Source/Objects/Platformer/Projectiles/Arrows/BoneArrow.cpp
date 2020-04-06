#include "BoneArrow.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

BoneArrow* BoneArrow::create()
{
	BoneArrow* instance = new BoneArrow();

	instance->autorelease();

	return instance;
}

BoneArrow::BoneArrow() : super(nullptr, CollisionObject::createBox(Size(128.0f, 16.0f)), (int)PlatformerCollisionType::PlayerWeapon, false)
{
	this->sprite = Sprite::create(ItemResources::Equipment_Weapons_Bows_BoneArrow);

	this->sprite->setRotation(270.0f);

	this->contentNode->addChild(this->sprite);
}

BoneArrow::~BoneArrow()
{
}

void BoneArrow::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}
