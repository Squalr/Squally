#include "InversionGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

InversionGenericPreview* InversionGenericPreview::create()
{
	InversionGenericPreview* instance = new InversionGenericPreview();

	instance->autorelease();

	return instance;
}

InversionGenericPreview::InversionGenericPreview()
{
}

InversionGenericPreview::~InversionGenericPreview()
{
}

HackablePreview* InversionGenericPreview::clone()
{
	return InversionGenericPreview::create();
}

void InversionGenericPreview::onEnter()
{
	super::onEnter();
}

void InversionGenericPreview::initializePositions()
{
	super::initializePositions();
}
