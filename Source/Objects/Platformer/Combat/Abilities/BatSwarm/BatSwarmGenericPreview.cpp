#include "BatSwarmGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/Critters/Bat.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BatSwarmGenericPreview* BatSwarmGenericPreview::create()
{
	BatSwarmGenericPreview* instance = new BatSwarmGenericPreview();

	instance->autorelease();

	return instance;
}

BatSwarmGenericPreview::BatSwarmGenericPreview()
{
	ValueMap valueMap;
	this->bat = Bat::deserialize(valueMap);

	this->bat->setRotation(180.0f);

	this->previewNode->addChild(this->bat);
}

BatSwarmGenericPreview::~BatSwarmGenericPreview()
{
}

HackablePreview* BatSwarmGenericPreview::clone()
{
	return BatSwarmGenericPreview::create();
}

void BatSwarmGenericPreview::onEnter()
{
	super::onEnter();
}

void BatSwarmGenericPreview::initializePositions()
{
	super::initializePositions();
}
