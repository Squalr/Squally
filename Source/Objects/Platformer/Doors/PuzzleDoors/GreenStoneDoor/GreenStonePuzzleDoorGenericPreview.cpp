#include "GreenStonePuzzleDoorGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

GreenStonePuzzleDoorGenericPreview* GreenStonePuzzleDoorGenericPreview::create()
{
	GreenStonePuzzleDoorGenericPreview* instance = new GreenStonePuzzleDoorGenericPreview();

	instance->autorelease();

	return instance;
}

GreenStonePuzzleDoorGenericPreview::GreenStonePuzzleDoorGenericPreview()
{
}

GreenStonePuzzleDoorGenericPreview::~GreenStonePuzzleDoorGenericPreview()
{
}

HackablePreview* GreenStonePuzzleDoorGenericPreview::clone()
{
	return GreenStonePuzzleDoorGenericPreview::create();
}

void GreenStonePuzzleDoorGenericPreview::onEnter()
{
	super::onEnter();
}

void GreenStonePuzzleDoorGenericPreview::initializePositions()
{
	super::initializePositions();
}
