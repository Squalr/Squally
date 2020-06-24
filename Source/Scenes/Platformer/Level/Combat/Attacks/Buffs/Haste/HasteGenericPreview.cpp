#include "HasteGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HasteGenericPreview* HasteGenericPreview::create()
{
	HasteGenericPreview* instance = new HasteGenericPreview();

	instance->autorelease();

	return instance;
}

HasteGenericPreview::HasteGenericPreview()
{
}

HasteGenericPreview::~HasteGenericPreview()
{
}

HackablePreview* HasteGenericPreview::clone()
{
	return HasteGenericPreview::create();
}

void HasteGenericPreview::onEnter()
{
	super::onEnter();
}

void HasteGenericPreview::initializePositions()
{
	super::initializePositions();
}
