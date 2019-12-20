#include "TempleDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TempleDoor::MapKeyTempleDoor = "temple-door";
const std::string TempleDoor::MapKeyColor = "color";

TempleDoor* TempleDoor::create(ValueMap& properties)
{
	TempleDoor* instance = new TempleDoor(properties);

	instance->autorelease();

	return instance;
}

TempleDoor::TempleDoor(ValueMap& properties) : super(properties, Size(420.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->topCollision = CollisionObject::create(PhysicsBody::createBox(Size(420.0f, 32.0f)), (CollisionType)PlatformerCollisionType::PassThrough, false, false);

	std::string color = GameUtils::getKeyOrDefault(this->properties, TempleDoor::MapKeyColor, Value("")).asString();

	if (color == "green")
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleGreenDoor);
	}
	else if (color == "green-skull")
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleSkullGreenDoor);
	}
	else if (color == "yellow-skull")
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleSkullDoor);
	}
	else
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleDoor);
	}

	this->addChild(this->door);
	this->addChild(this->topCollision);
}

TempleDoor::~TempleDoor()
{
}

void TempleDoor::initializePositions()
{
	super::initializePositions();

	this->topCollision->setPositionY(238.0f);
}
