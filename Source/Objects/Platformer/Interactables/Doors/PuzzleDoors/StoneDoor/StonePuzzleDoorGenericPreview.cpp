#include "StonePuzzleDoorGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

StonePuzzleDoorGenericPreview* StonePuzzleDoorGenericPreview::create()
{
	StonePuzzleDoorGenericPreview* instance = new StonePuzzleDoorGenericPreview();

	instance->autorelease();

	return instance;
}

StonePuzzleDoorGenericPreview::StonePuzzleDoorGenericPreview()
{
}

StonePuzzleDoorGenericPreview::~StonePuzzleDoorGenericPreview()
{
}

HackablePreview* StonePuzzleDoorGenericPreview::clone()
{
	return StonePuzzleDoorGenericPreview::create();
}

void StonePuzzleDoorGenericPreview::onEnter()
{
	super::onEnter();
}

void StonePuzzleDoorGenericPreview::initializePositions()
{
	super::initializePositions();
}
