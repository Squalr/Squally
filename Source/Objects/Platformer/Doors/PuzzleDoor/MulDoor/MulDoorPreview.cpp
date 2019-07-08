#include "MulDoorPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MulDoorPreview* MulDoorPreview::create()
{
	MulDoorPreview* instance = new MulDoorPreview();

	instance->autorelease();

	return instance;
}

MulDoorPreview::MulDoorPreview()
{
}

HackablePreview* MulDoorPreview::clone()
{
	return MulDoorPreview::create();
}

void MulDoorPreview::onEnter()
{
	super::onEnter();
}

void MulDoorPreview::initializePositions()
{
	super::initializePositions();
}
