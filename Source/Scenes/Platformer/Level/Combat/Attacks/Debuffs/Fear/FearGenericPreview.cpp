#include "FearGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FearGenericPreview* FearGenericPreview::create()
{
	FearGenericPreview* instance = new FearGenericPreview();

	instance->autorelease();

	return instance;
}

FearGenericPreview::FearGenericPreview()
{
}

FearGenericPreview::~FearGenericPreview()
{
}

HackablePreview* FearGenericPreview::clone()
{
	return FearGenericPreview::create();
}

void FearGenericPreview::onEnter()
{
	super::onEnter();
}

void FearGenericPreview::initializePositions()
{
	super::initializePositions();
}
