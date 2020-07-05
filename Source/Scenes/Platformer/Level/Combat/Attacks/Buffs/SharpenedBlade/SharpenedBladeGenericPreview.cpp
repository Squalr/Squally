#include "SharpenedBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SharpenedBladeGenericPreview* SharpenedBladeGenericPreview::create()
{
	SharpenedBladeGenericPreview* instance = new SharpenedBladeGenericPreview();

	instance->autorelease();

	return instance;
}

SharpenedBladeGenericPreview::SharpenedBladeGenericPreview()
{
}

SharpenedBladeGenericPreview::~SharpenedBladeGenericPreview()
{
}

HackablePreview* SharpenedBladeGenericPreview::clone()
{
	return SharpenedBladeGenericPreview::create();
}

void SharpenedBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void SharpenedBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
