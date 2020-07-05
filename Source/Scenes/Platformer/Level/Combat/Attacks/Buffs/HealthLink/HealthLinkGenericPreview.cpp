#include "HealthLinkGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HealthLinkGenericPreview* HealthLinkGenericPreview::create()
{
	HealthLinkGenericPreview* instance = new HealthLinkGenericPreview();

	instance->autorelease();

	return instance;
}

HealthLinkGenericPreview::HealthLinkGenericPreview()
{
}

HealthLinkGenericPreview::~HealthLinkGenericPreview()
{
}

HackablePreview* HealthLinkGenericPreview::clone()
{
	return HealthLinkGenericPreview::create();
}

void HealthLinkGenericPreview::onEnter()
{
	super::onEnter();
}

void HealthLinkGenericPreview::initializePositions()
{
	super::initializePositions();
}
