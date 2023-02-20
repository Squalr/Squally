#include "CursedBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CursedBladeGenericPreview* CursedBladeGenericPreview::create()
{
	CursedBladeGenericPreview* instance = new CursedBladeGenericPreview();

	instance->autorelease();

	return instance;
}

CursedBladeGenericPreview::CursedBladeGenericPreview()
{
}

CursedBladeGenericPreview::~CursedBladeGenericPreview()
{
}

HackablePreview* CursedBladeGenericPreview::clone()
{
	return CursedBladeGenericPreview::create();
}

void CursedBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void CursedBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
