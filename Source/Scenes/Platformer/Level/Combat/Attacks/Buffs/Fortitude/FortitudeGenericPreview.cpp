#include "FortitudeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FortitudeGenericPreview* FortitudeGenericPreview::create()
{
	FortitudeGenericPreview* instance = new FortitudeGenericPreview();

	instance->autorelease();

	return instance;
}

FortitudeGenericPreview::FortitudeGenericPreview()
{
}

FortitudeGenericPreview::~FortitudeGenericPreview()
{
}

HackablePreview* FortitudeGenericPreview::clone()
{
	return FortitudeGenericPreview::create();
}

void FortitudeGenericPreview::onEnter()
{
	super::onEnter();
}

void FortitudeGenericPreview::initializePositions()
{
	super::initializePositions();
}
