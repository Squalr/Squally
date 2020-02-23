#include "Ship.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Ship::MapKeyShip = "ship";

Ship* Ship::create(ValueMap& properties)
{
	Ship* instance = new Ship(properties);

	instance->autorelease();

	return instance;
}

Ship::Ship(ValueMap& properties) : super(properties)
{
	this->hull = Sprite::create(ObjectResources::Transportation_Ship_Hull);
	
	this->addChild(this->hull);
}

Ship::~Ship()
{
}

void Ship::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Ship::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void Ship::initializePositions()
{
	super::initializePositions();
}

void Ship::initializeListeners()
{
	super::initializeListeners();
}
