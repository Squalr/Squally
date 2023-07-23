#include "DazeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

DazeGenericPreview* DazeGenericPreview::create()
{
	DazeGenericPreview* instance = new DazeGenericPreview();

	instance->autorelease();

	return instance;
}

DazeGenericPreview::DazeGenericPreview()
{
}

DazeGenericPreview::~DazeGenericPreview()
{
}

HackablePreview* DazeGenericPreview::clone()
{
	return DazeGenericPreview::create();
}

void DazeGenericPreview::onEnter()
{
	super::onEnter();
}

void DazeGenericPreview::initializePositions()
{
	super::initializePositions();
}
