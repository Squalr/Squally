#include "CartLift.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CartLift::MapKey = "cart-lift";

CartLift* CartLift::create(cocos2d::ValueMap& properties)
{
	CartLift* instance = new CartLift(properties);

	instance->autorelease();

	return instance;
}

CartLift::CartLift(cocos2d::ValueMap& properties) : super(properties, Size(209.0f, 70.0f), ObjectResources::Physics_CartLift_Rail)
{
	this->platform = Sprite::create(ObjectResources::Physics_CartLift_Platform);
	this->startStop = Sprite::create(ObjectResources::Physics_CartLift_Stop);
	this->endStop = Sprite::create(ObjectResources::Physics_CartLift_Stop);

	this->endStop->setFlippedY(true);

	this->railingNode->addChild(this->startStop);
	this->railingNode->addChild(this->endStop);
	this->liftNode->addChild(this->platform);
}

CartLift::~CartLift()
{
}

void CartLift::initializePositions()
{
	super::initializePositions();

	const float Offset = 8.0f;
	const Vec2 StartPosition = this->movementDirection == MovementDirection::LeftRight ? Vec2(this->width / 2.0f + Offset, 0.0f) : Vec2(0.0f, this->height / 2.0f + Offset);

	this->startStop->setPosition(StartPosition);
	this->endStop->setPosition(-StartPosition);
}

float CartLift::getPadding()
{
	return 48.0f;
}
