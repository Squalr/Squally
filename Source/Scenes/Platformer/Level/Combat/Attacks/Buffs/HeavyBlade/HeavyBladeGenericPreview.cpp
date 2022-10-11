#include "HeavyBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HeavyBladeGenericPreview* HeavyBladeGenericPreview::create()
{
	HeavyBladeGenericPreview* instance = new HeavyBladeGenericPreview();

	instance->autorelease();

	return instance;
}

HeavyBladeGenericPreview::HeavyBladeGenericPreview()
{
}

HeavyBladeGenericPreview::~HeavyBladeGenericPreview()
{
}

HackablePreview* HeavyBladeGenericPreview::clone()
{
	return HeavyBladeGenericPreview::create();
}

void HeavyBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void HeavyBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
