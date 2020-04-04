#include "StoneSkinGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

StoneSkinGenericPreview* StoneSkinGenericPreview::create()
{
	StoneSkinGenericPreview* instance = new StoneSkinGenericPreview();

	instance->autorelease();

	return instance;
}

StoneSkinGenericPreview::StoneSkinGenericPreview()
{
}

StoneSkinGenericPreview::~StoneSkinGenericPreview()
{
}

HackablePreview* StoneSkinGenericPreview::clone()
{
	return StoneSkinGenericPreview::create();
}

void StoneSkinGenericPreview::onEnter()
{
	super::onEnter();
}

void StoneSkinGenericPreview::initializePositions()
{
	super::initializePositions();
}
