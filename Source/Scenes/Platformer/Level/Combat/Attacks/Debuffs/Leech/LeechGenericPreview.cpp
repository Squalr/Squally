#include "LeechGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

LeechGenericPreview* LeechGenericPreview::create()
{
	LeechGenericPreview* instance = new LeechGenericPreview();

	instance->autorelease();

	return instance;
}

LeechGenericPreview::LeechGenericPreview()
{
}

LeechGenericPreview::~LeechGenericPreview()
{
}

HackablePreview* LeechGenericPreview::clone()
{
	return LeechGenericPreview::create();
}

void LeechGenericPreview::onEnter()
{
	super::onEnter();
}

void LeechGenericPreview::initializePositions()
{
	super::initializePositions();
}
