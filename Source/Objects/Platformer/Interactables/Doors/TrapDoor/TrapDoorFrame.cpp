#include "TrapDoorFrame.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TrapDoorFrame::MapKeyTrapDoorFrame = "trap-door-frame";

TrapDoorFrame* TrapDoorFrame::create(ValueMap& properties)
{
	TrapDoorFrame* instance = new TrapDoorFrame(properties);

	instance->autorelease();

	return instance;
}

TrapDoorFrame::TrapDoorFrame(ValueMap& properties) : super(properties)
{
	this->trapDoorFrame = Sprite::create(ObjectResources::Doors_TrapDoor_TrapDoorFrame);

	this->isFlipped = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyFlipX, Value(false)).asBool();

	this->trapDoorFrame->setFlippedX(this->isFlipped);

	this->addChild(this->trapDoorFrame);
}

TrapDoorFrame::~TrapDoorFrame()
{
}

void TrapDoorFrame::onEnter()
{
	super::onEnter();
}

void TrapDoorFrame::initializePositions()
{
	super::initializePositions();

	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->trapDoorFrame->setPosition(Vec2(0.0f, -48.0f));

	this->trapDoorFrame->setPositionX(this->trapDoorFrame->getPositionX() * flipMultiplier);
}
