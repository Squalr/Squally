#include "RabiesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RabiesGenericPreview* RabiesGenericPreview::create()
{
	RabiesGenericPreview* instance = new RabiesGenericPreview();

	instance->autorelease();

	return instance;
}

RabiesGenericPreview::RabiesGenericPreview()
{
}

RabiesGenericPreview::~RabiesGenericPreview()
{
}

HackablePreview* RabiesGenericPreview::clone()
{
	return RabiesGenericPreview::create();
}

void RabiesGenericPreview::onEnter()
{
	super::onEnter();
}

void RabiesGenericPreview::initializePositions()
{
	super::initializePositions();
}
