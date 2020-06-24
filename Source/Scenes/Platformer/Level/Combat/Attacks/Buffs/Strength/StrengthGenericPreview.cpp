#include "StrengthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

StrengthGenericPreview* StrengthGenericPreview::create()
{
	StrengthGenericPreview* instance = new StrengthGenericPreview();

	instance->autorelease();

	return instance;
}

StrengthGenericPreview::StrengthGenericPreview()
{
}

StrengthGenericPreview::~StrengthGenericPreview()
{
}

HackablePreview* StrengthGenericPreview::clone()
{
	return StrengthGenericPreview::create();
}

void StrengthGenericPreview::onEnter()
{
	super::onEnter();
}

void StrengthGenericPreview::initializePositions()
{
	super::initializePositions();
}
