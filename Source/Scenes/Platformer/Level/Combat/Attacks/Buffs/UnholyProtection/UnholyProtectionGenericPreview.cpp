#include "UnholyProtectionGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

UnholyProtectionGenericPreview* UnholyProtectionGenericPreview::create()
{
	UnholyProtectionGenericPreview* instance = new UnholyProtectionGenericPreview();

	instance->autorelease();

	return instance;
}

UnholyProtectionGenericPreview::UnholyProtectionGenericPreview()
{
}

UnholyProtectionGenericPreview::~UnholyProtectionGenericPreview()
{
}

HackablePreview* UnholyProtectionGenericPreview::clone()
{
	return UnholyProtectionGenericPreview::create();
}

void UnholyProtectionGenericPreview::onEnter()
{
	super::onEnter();
}

void UnholyProtectionGenericPreview::initializePositions()
{
	super::initializePositions();
}
