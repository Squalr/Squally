#include "DiseasedGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

DiseasedGenericPreview* DiseasedGenericPreview::create()
{
	DiseasedGenericPreview* instance = new DiseasedGenericPreview();

	instance->autorelease();

	return instance;
}

DiseasedGenericPreview::DiseasedGenericPreview()
{
}

DiseasedGenericPreview::~DiseasedGenericPreview()
{
}

HackablePreview* DiseasedGenericPreview::clone()
{
	return DiseasedGenericPreview::create();
}

void DiseasedGenericPreview::onEnter()
{
	super::onEnter();
}

void DiseasedGenericPreview::initializePositions()
{
	super::initializePositions();
}
