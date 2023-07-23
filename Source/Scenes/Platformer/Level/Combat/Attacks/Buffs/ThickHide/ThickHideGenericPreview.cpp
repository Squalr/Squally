#include "ThickHideGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ThickHideGenericPreview* ThickHideGenericPreview::create()
{
	ThickHideGenericPreview* instance = new ThickHideGenericPreview();

	instance->autorelease();

	return instance;
}

ThickHideGenericPreview::ThickHideGenericPreview()
{
}

ThickHideGenericPreview::~ThickHideGenericPreview()
{
}

HackablePreview* ThickHideGenericPreview::clone()
{
	return ThickHideGenericPreview::create();
}

void ThickHideGenericPreview::onEnter()
{
	super::onEnter();
}

void ThickHideGenericPreview::initializePositions()
{
	super::initializePositions();
}
