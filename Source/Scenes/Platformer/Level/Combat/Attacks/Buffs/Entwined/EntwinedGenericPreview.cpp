#include "EntwinedGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EntwinedGenericPreview* EntwinedGenericPreview::create()
{
	EntwinedGenericPreview* instance = new EntwinedGenericPreview();

	instance->autorelease();

	return instance;
}

EntwinedGenericPreview::EntwinedGenericPreview()
{
}

EntwinedGenericPreview::~EntwinedGenericPreview()
{
}

HackablePreview* EntwinedGenericPreview::clone()
{
	return EntwinedGenericPreview::create();
}

void EntwinedGenericPreview::onEnter()
{
	super::onEnter();
}

void EntwinedGenericPreview::initializePositions()
{
	super::initializePositions();
}
