#include "ScreamingDoor.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string ScreamingDoor::MapKey = "screaming-door";

ScreamingDoor* ScreamingDoor::create(ValueMap& properties)
{
	ScreamingDoor* instance = new ScreamingDoor(properties);

	instance->autorelease();

	return instance;
}

ScreamingDoor::ScreamingDoor(ValueMap& properties) : super(properties, Size(256.0f, 420.0f), Vec2(0.0f, -320.0f))
{
	this->screamingDoor = Sprite::create(ObjectResources::Doors_ScreamingDoor_ScreamingDoor);

	this->backNode->addChild(this->screamingDoor);
}

ScreamingDoor::~ScreamingDoor()
{
}

void ScreamingDoor::onEnter()
{
	super::onEnter();
}

void ScreamingDoor::initializePositions()
{
	super::initializePositions();

	this->screamingDoor->setPosition(Vec2(0.0f, 0.0f));
}

void ScreamingDoor::initializeListeners()
{
	super::initializeListeners();
}

Vec2 ScreamingDoor::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* ScreamingDoor::createDefaultPreview()
{
	return nullptr;
}
