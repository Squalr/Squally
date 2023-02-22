#include "FireRainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/Critters/Bat.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FireRainGenericPreview* FireRainGenericPreview::create()
{
	FireRainGenericPreview* instance = new FireRainGenericPreview();

	instance->autorelease();

	return instance;
}

FireRainGenericPreview::FireRainGenericPreview()
{
	ValueMap valueMap;
	this->bat = Bat::deserialize(valueMap);

	this->bat->setRotation(180.0f);

	this->previewNode->addChild(this->bat);
}

FireRainGenericPreview::~FireRainGenericPreview()
{
}

HackablePreview* FireRainGenericPreview::clone()
{
	return FireRainGenericPreview::create();
}

void FireRainGenericPreview::onEnter()
{
	super::onEnter();
}

void FireRainGenericPreview::initializePositions()
{
	super::initializePositions();
}
