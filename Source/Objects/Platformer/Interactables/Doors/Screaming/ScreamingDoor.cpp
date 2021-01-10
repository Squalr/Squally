#include "ScreamingDoor.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Objects/Platformer/Interactables/Doors/Screaming/TrackingEye.h"

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
	this->leftEye = TrackingEye::create();
	this->rightEye = TrackingEye::create();

	this->leftEye->pair(this->rightEye);
	this->rightEye->pair(this->leftEye);

	this->contentNode->addChild(this->screamingDoor);
	this->contentNode->addChild(this->leftEye);
	this->contentNode->addChild(this->rightEye);
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
	this->leftEye->setPosition(Vec2(-108.0f, 76.0f));
	this->rightEye->setPosition(Vec2(96.0f, 76.0f));
}

void ScreamingDoor::initializeListeners()
{
	super::initializeListeners();
}
