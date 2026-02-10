#include "ChanceGenericPreview.h"

#include "2d/CCActionEase.h"
#include "2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ChanceGenericPreview* ChanceGenericPreview::create()
{
	ChanceGenericPreview* instance = new ChanceGenericPreview();

	instance->autorelease();

	return instance;
}

ChanceGenericPreview::ChanceGenericPreview()
{
}

ChanceGenericPreview::~ChanceGenericPreview()
{
}

HackablePreview* ChanceGenericPreview::clone()
{
	return ChanceGenericPreview::create();
}

void ChanceGenericPreview::onEnter()
{
	super::onEnter();
}

void ChanceGenericPreview::initializePositions()
{
	super::initializePositions();
}
