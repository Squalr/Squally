#include "ZombieGraspGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ZombieGraspGenericPreview* ZombieGraspGenericPreview::create()
{
	ZombieGraspGenericPreview* instance = new ZombieGraspGenericPreview();

	instance->autorelease();

	return instance;
}

ZombieGraspGenericPreview::ZombieGraspGenericPreview()
{
}

ZombieGraspGenericPreview::~ZombieGraspGenericPreview()
{
}

HackablePreview* ZombieGraspGenericPreview::clone()
{
	return ZombieGraspGenericPreview::create();
}

void ZombieGraspGenericPreview::onEnter()
{
	super::onEnter();
}

void ZombieGraspGenericPreview::initializePositions()
{
	super::initializePositions();
}
