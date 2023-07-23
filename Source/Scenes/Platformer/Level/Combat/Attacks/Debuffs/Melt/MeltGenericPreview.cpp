#include "MeltGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

MeltGenericPreview* MeltGenericPreview::create()
{
	MeltGenericPreview* instance = new MeltGenericPreview();

	instance->autorelease();

	return instance;
}

MeltGenericPreview::MeltGenericPreview()
{
}

MeltGenericPreview::~MeltGenericPreview()
{
}

HackablePreview* MeltGenericPreview::clone()
{
	return MeltGenericPreview::create();
}

void MeltGenericPreview::onEnter()
{
	super::onEnter();
}

void MeltGenericPreview::initializePositions()
{
	super::initializePositions();
}
