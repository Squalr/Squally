#include "SeekingBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SeekingBladeGenericPreview* SeekingBladeGenericPreview::create()
{
	SeekingBladeGenericPreview* instance = new SeekingBladeGenericPreview();

	instance->autorelease();

	return instance;
}

SeekingBladeGenericPreview::SeekingBladeGenericPreview()
{
}

SeekingBladeGenericPreview::~SeekingBladeGenericPreview()
{
}

HackablePreview* SeekingBladeGenericPreview::clone()
{
	return SeekingBladeGenericPreview::create();
}

void SeekingBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void SeekingBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
