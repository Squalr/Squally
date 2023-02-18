#include "FocusGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FocusGenericPreview* FocusGenericPreview::create()
{
	FocusGenericPreview* instance = new FocusGenericPreview();

	instance->autorelease();

	return instance;
}

FocusGenericPreview::FocusGenericPreview()
{
}

FocusGenericPreview::~FocusGenericPreview()
{
}

HackablePreview* FocusGenericPreview::clone()
{
	return FocusGenericPreview::create();
}

void FocusGenericPreview::onEnter()
{
	super::onEnter();
}

void FocusGenericPreview::initializePositions()
{
	super::initializePositions();
}
