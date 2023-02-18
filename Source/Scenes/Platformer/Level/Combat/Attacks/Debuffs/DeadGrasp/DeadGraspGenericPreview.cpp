#include "DeadGraspGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

DeadGraspGenericPreview* DeadGraspGenericPreview::create()
{
	DeadGraspGenericPreview* instance = new DeadGraspGenericPreview();

	instance->autorelease();

	return instance;
}

DeadGraspGenericPreview::DeadGraspGenericPreview()
{
}

DeadGraspGenericPreview::~DeadGraspGenericPreview()
{
}

HackablePreview* DeadGraspGenericPreview::clone()
{
	return DeadGraspGenericPreview::create();
}

void DeadGraspGenericPreview::onEnter()
{
	super::onEnter();
}

void DeadGraspGenericPreview::initializePositions()
{
	super::initializePositions();
}
