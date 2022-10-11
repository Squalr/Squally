#include "PactOfTheAncientsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

PactOfTheAncientsGenericPreview* PactOfTheAncientsGenericPreview::create()
{
	PactOfTheAncientsGenericPreview* instance = new PactOfTheAncientsGenericPreview();

	instance->autorelease();

	return instance;
}

PactOfTheAncientsGenericPreview::PactOfTheAncientsGenericPreview()
{
}

PactOfTheAncientsGenericPreview::~PactOfTheAncientsGenericPreview()
{
}

HackablePreview* PactOfTheAncientsGenericPreview::clone()
{
	return PactOfTheAncientsGenericPreview::create();
}

void PactOfTheAncientsGenericPreview::onEnter()
{
	super::onEnter();
}

void PactOfTheAncientsGenericPreview::initializePositions()
{
	super::initializePositions();
}
