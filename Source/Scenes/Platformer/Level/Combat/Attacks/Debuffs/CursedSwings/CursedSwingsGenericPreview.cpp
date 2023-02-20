#include "CursedSwingsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CursedSwingsGenericPreview* CursedSwingsGenericPreview::create()
{
	CursedSwingsGenericPreview* instance = new CursedSwingsGenericPreview();

	instance->autorelease();

	return instance;
}

CursedSwingsGenericPreview::CursedSwingsGenericPreview()
{
}

CursedSwingsGenericPreview::~CursedSwingsGenericPreview()
{
}

HackablePreview* CursedSwingsGenericPreview::clone()
{
	return CursedSwingsGenericPreview::create();
}

void CursedSwingsGenericPreview::onEnter()
{
	super::onEnter();
}

void CursedSwingsGenericPreview::initializePositions()
{
	super::initializePositions();
}
