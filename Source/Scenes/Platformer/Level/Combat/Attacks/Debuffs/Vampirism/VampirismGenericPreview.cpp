#include "VampirismGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

VampirismGenericPreview* VampirismGenericPreview::create()
{
	VampirismGenericPreview* instance = new VampirismGenericPreview();

	instance->autorelease();

	return instance;
}

VampirismGenericPreview::VampirismGenericPreview()
{
}

VampirismGenericPreview::~VampirismGenericPreview()
{
}

HackablePreview* VampirismGenericPreview::clone()
{
	return VampirismGenericPreview::create();
}

void VampirismGenericPreview::onEnter()
{
	super::onEnter();
}

void VampirismGenericPreview::initializePositions()
{
	super::initializePositions();
}
