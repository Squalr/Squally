#include "BlessingOfTheAncientsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BlessingOfTheAncientsGenericPreview* BlessingOfTheAncientsGenericPreview::create()
{
	BlessingOfTheAncientsGenericPreview* instance = new BlessingOfTheAncientsGenericPreview();

	instance->autorelease();

	return instance;
}

BlessingOfTheAncientsGenericPreview::BlessingOfTheAncientsGenericPreview()
{
}

BlessingOfTheAncientsGenericPreview::~BlessingOfTheAncientsGenericPreview()
{
}

HackablePreview* BlessingOfTheAncientsGenericPreview::clone()
{
	return BlessingOfTheAncientsGenericPreview::create();
}

void BlessingOfTheAncientsGenericPreview::onEnter()
{
	super::onEnter();
}

void BlessingOfTheAncientsGenericPreview::initializePositions()
{
	super::initializePositions();
}
