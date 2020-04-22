#include "Ship.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Ship::MapKey = "ship";

Ship* Ship::create(ValueMap& properties)
{
	Ship* instance = new Ship(properties);

	instance->autorelease();

	return instance;
}

Ship::Ship(ValueMap& properties) : super(properties)
{
	this->ship = SmartAnimationNode::create(ObjectResources::Transportation_Ship_Animations);
	
	this->addChild(this->ship);
}

Ship::~Ship()
{
}
