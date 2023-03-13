#include "ManifestGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ManifestGenericPreview* ManifestGenericPreview::create()
{
	ManifestGenericPreview* instance = new ManifestGenericPreview();

	instance->autorelease();

	return instance;
}

ManifestGenericPreview::ManifestGenericPreview()
{
}

ManifestGenericPreview::~ManifestGenericPreview()
{
}

HackablePreview* ManifestGenericPreview::clone()
{
	return ManifestGenericPreview::create();
}

void ManifestGenericPreview::onEnter()
{
	super::onEnter();
}

void ManifestGenericPreview::initializePositions()
{
	super::initializePositions();
}
