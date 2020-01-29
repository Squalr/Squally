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
	this->emblem = nullptr;
	this->emblemOffset = Vec2::ZERO;

	std::string color = GameUtils::getKeyOrDefault(this->properties, TempleDoor::MapKeyColor, Value("")).asString();

	if (color == "green" || color == "green-skull" || color == "green-up" || color == "green-down")
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleGreenDoor);
	}
	else // if (color == "yellow" || color == "yellow-skull" || color == "yellow-up" || color == "yellow-down")
	{
		this->door = Sprite::create(ObjectResources::Doors_Temple_TempleDoor);
	}
	
	if (color == "yellow-skull" || color == "green-skull")
	{
		this->emblem = Sprite::create(ObjectResources::Doors_Temple_Skull);
		this->emblemOffset = Vec2(0.0f, 116.0f);
	}
	else if (color == "yellow-up" || color == "green-up")
	{
		this->emblem = Sprite::create(ObjectResources::Doors_Temple_UpArrow);
		this->emblemOffset = Vec2(0.0f, 172.0f);
	}
	else if (color == "yellow-down" || color == "green-down")
	{
		this->emblem = Sprite::create(ObjectResources::Doors_Temple_DownArrow);
		this->emblemOffset = Vec2(0.0f, 172.0f);
	}

	this->addChild(this->door);

	if (this->emblem != nullptr)
	{
		this->addChild(this->emblem);
	}

	this->addChild(this->topCollision);
}

TempleDoor::~TempleDoor()
{
}

void TempleDoor::initializePositions()
{
	super::initializePositions();

	if (this->emblem != nullptr)
	{
		this->emblem->setPosition(this->emblemOffset);
	}

	this->topCollision->setPositionY(238.0f);
}
