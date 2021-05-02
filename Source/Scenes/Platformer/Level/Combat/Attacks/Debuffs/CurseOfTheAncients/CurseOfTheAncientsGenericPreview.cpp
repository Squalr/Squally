#include "CurseOfTheAncientsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CurseOfTheAncientsGenericPreview* CurseOfTheAncientsGenericPreview::create()
{
	CurseOfTheAncientsGenericPreview* instance = new CurseOfTheAncientsGenericPreview();

	instance->autorelease();

	return instance;
}

CurseOfTheAncientsGenericPreview::CurseOfTheAncientsGenericPreview()
{
}

CurseOfTheAncientsGenericPreview::~CurseOfTheAncientsGenericPreview()
{
}

HackablePreview* CurseOfTheAncientsGenericPreview::clone()
{
	return CurseOfTheAncientsGenericPreview::create();
}

void CurseOfTheAncientsGenericPreview::onEnter()
{
	super::onEnter();
}

void CurseOfTheAncientsGenericPreview::initializePositions()
{
	super::initializePositions();
}
