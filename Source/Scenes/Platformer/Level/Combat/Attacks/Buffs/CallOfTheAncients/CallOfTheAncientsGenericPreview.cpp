#include "CallOfTheAncientsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CallOfTheAncientsGenericPreview* CallOfTheAncientsGenericPreview::create()
{
	CallOfTheAncientsGenericPreview* instance = new CallOfTheAncientsGenericPreview();

	instance->autorelease();

	return instance;
}

CallOfTheAncientsGenericPreview::CallOfTheAncientsGenericPreview()
{
}

CallOfTheAncientsGenericPreview::~CallOfTheAncientsGenericPreview()
{
}

HackablePreview* CallOfTheAncientsGenericPreview::clone()
{
	return CallOfTheAncientsGenericPreview::create();
}

void CallOfTheAncientsGenericPreview::onEnter()
{
	super::onEnter();
}

void CallOfTheAncientsGenericPreview::initializePositions()
{
	super::initializePositions();
}
