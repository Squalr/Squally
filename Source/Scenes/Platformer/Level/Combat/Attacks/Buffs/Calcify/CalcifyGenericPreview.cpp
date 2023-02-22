#include "CalcifyGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CalcifyGenericPreview* CalcifyGenericPreview::create()
{
	CalcifyGenericPreview* instance = new CalcifyGenericPreview();

	instance->autorelease();

	return instance;
}

CalcifyGenericPreview::CalcifyGenericPreview()
{
}

CalcifyGenericPreview::~CalcifyGenericPreview()
{
}

HackablePreview* CalcifyGenericPreview::clone()
{
	return CalcifyGenericPreview::create();
}

void CalcifyGenericPreview::onEnter()
{
	super::onEnter();
}

void CalcifyGenericPreview::initializePositions()
{
	super::initializePositions();
}
