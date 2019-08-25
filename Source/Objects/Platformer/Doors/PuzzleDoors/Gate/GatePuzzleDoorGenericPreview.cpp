#include "GatePuzzleDoorGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

GatePuzzleDoorGenericPreview* GatePuzzleDoorGenericPreview::create()
{
	GatePuzzleDoorGenericPreview* instance = new GatePuzzleDoorGenericPreview();

	instance->autorelease();

	return instance;
}

GatePuzzleDoorGenericPreview::GatePuzzleDoorGenericPreview()
{
}

GatePuzzleDoorGenericPreview::~GatePuzzleDoorGenericPreview()
{
}

HackablePreview* GatePuzzleDoorGenericPreview::clone()
{
	return GatePuzzleDoorGenericPreview::create();
}

void GatePuzzleDoorGenericPreview::onEnter()
{
	super::onEnter();
}

void GatePuzzleDoorGenericPreview::initializePositions()
{
	super::initializePositions();
}
