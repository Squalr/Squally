#include "ImmortalityGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ImmortalityGenericPreview* ImmortalityGenericPreview::create()
{
	ImmortalityGenericPreview* instance = new ImmortalityGenericPreview();

	instance->autorelease();

	return instance;
}

ImmortalityGenericPreview::ImmortalityGenericPreview()
{
}

ImmortalityGenericPreview::~ImmortalityGenericPreview()
{
}

HackablePreview* ImmortalityGenericPreview::clone()
{
	return ImmortalityGenericPreview::create();
}

void ImmortalityGenericPreview::onEnter()
{
	super::onEnter();
}

void ImmortalityGenericPreview::initializePositions()
{
	super::initializePositions();
}
