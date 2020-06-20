#include "UndyingGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

UndyingGenericPreview* UndyingGenericPreview::create()
{
	UndyingGenericPreview* instance = new UndyingGenericPreview();

	instance->autorelease();

	return instance;
}

UndyingGenericPreview::UndyingGenericPreview()
{
}

UndyingGenericPreview::~UndyingGenericPreview()
{
}

HackablePreview* UndyingGenericPreview::clone()
{
	return UndyingGenericPreview::create();
}

void UndyingGenericPreview::onEnter()
{
	super::onEnter();
}

void UndyingGenericPreview::initializePositions()
{
	super::initializePositions();
}
