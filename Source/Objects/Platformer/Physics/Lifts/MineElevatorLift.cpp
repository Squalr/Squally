#include "MineElevatorLift.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineElevatorLift::MapKey = "mine-elevator";

MineElevatorLift* MineElevatorLift::create(cocos2d::ValueMap& properties)
{
	MineElevatorLift* instance = new MineElevatorLift(properties);

	instance->autorelease();

	return instance;
}

MineElevatorLift::MineElevatorLift(cocos2d::ValueMap& properties) : super(properties, Size(546.0f, 64.0f), ObjectResources::Physics_CartLift_Rail)
{
	this->elevator = Sprite::create(ObjectResources::Physics_MineElevator_MineElevatorBase);
	this->gear = Sprite::create(ObjectResources::Physics_MineElevator_MineElevatorGear);
	this->gearShaft = Sprite::create(ObjectResources::Physics_MineElevator_MineElevatorGearShaft);

	this->liftNode->addChild(this->gearShaft);
	this->liftNode->addChild(this->gear);
	this->liftNode->addChild(this->elevator);
}

MineElevatorLift::~MineElevatorLift()
{
}

void MineElevatorLift::onEnter()
{
	super::onEnter();

	this->gear->runAction(RepeatForever::create(RotateBy::create(2.0f, 360.0f)));
}

void MineElevatorLift::initializePositions()
{
	super::initializePositions();
	
	const float OffsetY = this->elevator->getContentSize().height / 2.0f - 32.0f;

	this->elevator->setPosition(Vec2(0.0f, OffsetY));
	this->gear->setPosition(Vec2(0.0f, OffsetY + 356.0f));
	this->gearShaft->setPosition(Vec2(0.0f, OffsetY + 296.0f));
}

Vec2 MineElevatorLift::getRailsOffset()
{
    return Vec2(0.0f, this->elevator->getContentSize().height);
}

float MineElevatorLift::getPadding()
{
	return 48.0f;
}
