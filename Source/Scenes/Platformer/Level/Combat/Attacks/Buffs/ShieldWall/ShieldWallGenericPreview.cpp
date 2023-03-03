#include "ShieldWallGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ShieldWallGenericPreview* ShieldWallGenericPreview::create()
{
	ShieldWallGenericPreview* instance = new ShieldWallGenericPreview();

	instance->autorelease();

	return instance;
}

ShieldWallGenericPreview::ShieldWallGenericPreview()
{
}

ShieldWallGenericPreview::~ShieldWallGenericPreview()
{
}

HackablePreview* ShieldWallGenericPreview::clone()
{
	return ShieldWallGenericPreview::create();
}

void ShieldWallGenericPreview::onEnter()
{
	super::onEnter();
}

void ShieldWallGenericPreview::initializePositions()
{
	super::initializePositions();
}
