#include "FuryGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FuryGenericPreview* FuryGenericPreview::create()
{
	FuryGenericPreview* instance = new FuryGenericPreview();

	instance->autorelease();

	return instance;
}

FuryGenericPreview::FuryGenericPreview()
{
}

FuryGenericPreview::~FuryGenericPreview()
{
}

HackablePreview* FuryGenericPreview::clone()
{
	return FuryGenericPreview::create();
}

void FuryGenericPreview::onEnter()
{
	super::onEnter();
}

void FuryGenericPreview::initializePositions()
{
	super::initializePositions();
}
