#include "ManaLifeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ManaLifeGenericPreview* ManaLifeGenericPreview::create()
{
	ManaLifeGenericPreview* instance = new ManaLifeGenericPreview();

	instance->autorelease();

	return instance;
}

ManaLifeGenericPreview::ManaLifeGenericPreview()
{
}

ManaLifeGenericPreview::~ManaLifeGenericPreview()
{
}

HackablePreview* ManaLifeGenericPreview::clone()
{
	return ManaLifeGenericPreview::create();
}

void ManaLifeGenericPreview::onEnter()
{
	super::onEnter();
}

void ManaLifeGenericPreview::initializePositions()
{
	super::initializePositions();
}
