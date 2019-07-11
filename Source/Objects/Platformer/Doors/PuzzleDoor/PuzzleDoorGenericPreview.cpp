#include "PuzzleDoorGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

PuzzleDoorGenericPreview* PuzzleDoorGenericPreview::create()
{
	PuzzleDoorGenericPreview* instance = new PuzzleDoorGenericPreview();

	instance->autorelease();

	return instance;
}

PuzzleDoorGenericPreview::PuzzleDoorGenericPreview()
{
}

HackablePreview* PuzzleDoorGenericPreview::clone()
{
	return PuzzleDoorGenericPreview::create();
}

void PuzzleDoorGenericPreview::onEnter()
{
	super::onEnter();
}

void PuzzleDoorGenericPreview::initializePositions()
{
	super::initializePositions();
}
