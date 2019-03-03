#include "StoneButton.h"

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

const std::string StoneButton::MapKeyStoneButton = "stone-button";

StoneButton* StoneButton::create(ValueMap& initProperties)
{
	StoneButton* instance = new StoneButton(initProperties);

	instance->autorelease();

	return instance;
}

StoneButton::StoneButton(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->box = Sprite::create(ObjectResources::Switches_StoneButton_StoneButtonBase);
	this->boxCollision = CollisionObject::create(PhysicsBody::createBox(Size(128.0f, 128.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);

	this->box->addChild(this->boxCollision);
	this->addChild(this->box);
}

StoneButton::~StoneButton()
{
}

void StoneButton::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void StoneButton::initializePositions()
{
	super::initializePositions();
}

void StoneButton::update(float dt)
{
	super::update(dt);
}

Vec2 StoneButton::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void StoneButton::registerHackables()
{
	super::registerHackables();
}
