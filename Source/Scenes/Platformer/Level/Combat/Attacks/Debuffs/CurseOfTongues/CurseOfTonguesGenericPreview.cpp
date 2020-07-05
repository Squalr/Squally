#include "CurseOfTonguesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CurseOfTonguesGenericPreview* CurseOfTonguesGenericPreview::create()
{
	CurseOfTonguesGenericPreview* instance = new CurseOfTonguesGenericPreview();

	instance->autorelease();

	return instance;
}

CurseOfTonguesGenericPreview::CurseOfTonguesGenericPreview()
{
}

CurseOfTonguesGenericPreview::~CurseOfTonguesGenericPreview()
{
}

HackablePreview* CurseOfTonguesGenericPreview::clone()
{
	return CurseOfTonguesGenericPreview::create();
}

void CurseOfTonguesGenericPreview::onEnter()
{
	super::onEnter();
}

void CurseOfTonguesGenericPreview::initializePositions()
{
	super::initializePositions();
}
