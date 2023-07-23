#include "ScaldingBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ScaldingBladeGenericPreview* ScaldingBladeGenericPreview::create()
{
	ScaldingBladeGenericPreview* instance = new ScaldingBladeGenericPreview();

	instance->autorelease();

	return instance;
}

ScaldingBladeGenericPreview::ScaldingBladeGenericPreview()
{
}

ScaldingBladeGenericPreview::~ScaldingBladeGenericPreview()
{
}

HackablePreview* ScaldingBladeGenericPreview::clone()
{
	return ScaldingBladeGenericPreview::create();
}

void ScaldingBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void ScaldingBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
