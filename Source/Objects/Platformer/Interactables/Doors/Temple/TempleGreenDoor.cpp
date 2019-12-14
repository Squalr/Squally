#include "TempleGreenDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TempleGreenDoor::MapKeyTempleGreenDoor = "temple-green-door";

TempleGreenDoor* TempleGreenDoor::create(ValueMap& properties)
{
	TempleGreenDoor* instance = new TempleGreenDoor(properties);

	instance->autorelease();

	return instance;
}

TempleGreenDoor::TempleGreenDoor(ValueMap& properties) : super(properties, Size(420.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->door = Sprite::create(ObjectResources::Doors_Temple_TempleGreenDoor);

	this->addChild(this->door);
}

TempleGreenDoor::~TempleGreenDoor()
{
}

void TempleGreenDoor::initializePositions()
{
	super::initializePositions();
}
