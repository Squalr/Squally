#include "FogOfWarGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/DecorResources.h"

using namespace cocos2d;

FogOfWarGenericPreview* FogOfWarGenericPreview::create()
{
	FogOfWarGenericPreview* instance = new FogOfWarGenericPreview();

	instance->autorelease();

	return instance;
}

FogOfWarGenericPreview::FogOfWarGenericPreview()
{
	this->fog = Sprite::create(DecorResources::Generic_Background_Fog4);

	this->fog->setScale(0.4f);

	this->previewNode->addChild(this->fog);
}

FogOfWarGenericPreview::~FogOfWarGenericPreview()
{
}

HackablePreview* FogOfWarGenericPreview::clone()
{
	return FogOfWarGenericPreview::create();
}

void FogOfWarGenericPreview::onEnter()
{
	super::onEnter();
}

void FogOfWarGenericPreview::initializePositions()
{
	super::initializePositions();
}
