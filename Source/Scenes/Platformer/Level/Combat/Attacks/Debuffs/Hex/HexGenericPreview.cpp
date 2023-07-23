#include "HexGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HexGenericPreview* HexGenericPreview::create()
{
	HexGenericPreview* instance = new HexGenericPreview();

	instance->autorelease();

	return instance;
}

HexGenericPreview::HexGenericPreview()
{
}

HexGenericPreview::~HexGenericPreview()
{
}

HackablePreview* HexGenericPreview::clone()
{
	return HexGenericPreview::create();
}

void HexGenericPreview::onEnter()
{
	super::onEnter();
}

void HexGenericPreview::initializePositions()
{
	super::initializePositions();
}
