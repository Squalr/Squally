#include "EnrageGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EnrageGenericPreview* EnrageGenericPreview::create()
{
	EnrageGenericPreview* instance = new EnrageGenericPreview();

	instance->autorelease();

	return instance;
}

EnrageGenericPreview::EnrageGenericPreview()
{
}

EnrageGenericPreview::~EnrageGenericPreview()
{
}

HackablePreview* EnrageGenericPreview::clone()
{
	return EnrageGenericPreview::create();
}

void EnrageGenericPreview::onEnter()
{
	super::onEnter();
}

void EnrageGenericPreview::initializePositions()
{
	super::initializePositions();
}
