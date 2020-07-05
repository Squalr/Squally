#include "BrokenBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BrokenBladeGenericPreview* BrokenBladeGenericPreview::create()
{
	BrokenBladeGenericPreview* instance = new BrokenBladeGenericPreview();

	instance->autorelease();

	return instance;
}

BrokenBladeGenericPreview::BrokenBladeGenericPreview()
{
}

BrokenBladeGenericPreview::~BrokenBladeGenericPreview()
{
}

HackablePreview* BrokenBladeGenericPreview::clone()
{
	return BrokenBladeGenericPreview::create();
}

void BrokenBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void BrokenBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
