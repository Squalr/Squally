#include "ArcaneProtectionGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ArcaneProtectionGenericPreview* ArcaneProtectionGenericPreview::create()
{
	ArcaneProtectionGenericPreview* instance = new ArcaneProtectionGenericPreview();

	instance->autorelease();

	return instance;
}

ArcaneProtectionGenericPreview::ArcaneProtectionGenericPreview()
{
}

ArcaneProtectionGenericPreview::~ArcaneProtectionGenericPreview()
{
}

HackablePreview* ArcaneProtectionGenericPreview::clone()
{
	return ArcaneProtectionGenericPreview::create();
}

void ArcaneProtectionGenericPreview::onEnter()
{
	super::onEnter();
}

void ArcaneProtectionGenericPreview::initializePositions()
{
	super::initializePositions();
}
