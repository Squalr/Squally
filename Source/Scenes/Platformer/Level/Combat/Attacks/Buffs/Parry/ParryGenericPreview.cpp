#include "ParryGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ParryGenericPreview* ParryGenericPreview::create()
{
	ParryGenericPreview* instance = new ParryGenericPreview();

	instance->autorelease();

	return instance;
}

ParryGenericPreview::ParryGenericPreview()
{
}

ParryGenericPreview::~ParryGenericPreview()
{
}

HackablePreview* ParryGenericPreview::clone()
{
	return ParryGenericPreview::create();
}

void ParryGenericPreview::onEnter()
{
	super::onEnter();
}

void ParryGenericPreview::initializePositions()
{
	super::initializePositions();
}
