#include "UnholyBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

UnholyBladeGenericPreview* UnholyBladeGenericPreview::create()
{
	UnholyBladeGenericPreview* instance = new UnholyBladeGenericPreview();

	instance->autorelease();

	return instance;
}

UnholyBladeGenericPreview::UnholyBladeGenericPreview()
{
}

UnholyBladeGenericPreview::~UnholyBladeGenericPreview()
{
}

HackablePreview* UnholyBladeGenericPreview::clone()
{
	return UnholyBladeGenericPreview::create();
}

void UnholyBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void UnholyBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
