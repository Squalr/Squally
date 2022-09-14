#include "RockSlideGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RockSlideGenericPreview* RockSlideGenericPreview::create(std::string rockResource)
{
	RockSlideGenericPreview* instance = new RockSlideGenericPreview(rockResource);

	instance->autorelease();

	return instance;
}

RockSlideGenericPreview::RockSlideGenericPreview(std::string rockResource)
{
	this->rockResource = rockResource;
	this->rock = Sprite::create(rockResource);

	this->rock->setRotation(180.0f);

	this->previewNode->addChild(this->rock);
}

RockSlideGenericPreview::~RockSlideGenericPreview()
{
}

HackablePreview* RockSlideGenericPreview::clone()
{
	return RockSlideGenericPreview::create(this->rockResource);
}

void RockSlideGenericPreview::onEnter()
{
	super::onEnter();
}

void RockSlideGenericPreview::initializePositions()
{
	super::initializePositions();
}
