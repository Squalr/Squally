#include "TempleDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TempleDoor::MapKeyTempleDoor = "temple-door";

TempleDoor* TempleDoor::create(ValueMap& properties)
{
	TempleDoor* instance = new TempleDoor(properties);

	instance->autorelease();

	return instance;
}

TempleDoor::TempleDoor(ValueMap& properties) : super(properties, Size(420.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->door = Sprite::create(ObjectResources::Doors_Temple_TempleDoor);
	this->topCollision = CollisionObject::create(PhysicsBody::createBox(Size(420.0f, 32.0f)), (CollisionType)PlatformerCollisionType::PassThrough, false, false);

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
