#include "DefensiveStanceGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

DefensiveStanceGenericPreview* DefensiveStanceGenericPreview::create()
{
	DefensiveStanceGenericPreview* instance = new DefensiveStanceGenericPreview();

	instance->autorelease();

	return instance;
}

DefensiveStanceGenericPreview::DefensiveStanceGenericPreview()
{
}

DefensiveStanceGenericPreview::~DefensiveStanceGenericPreview()
{
}

HackablePreview* DefensiveStanceGenericPreview::clone()
{
	return DefensiveStanceGenericPreview::create();
}

void DefensiveStanceGenericPreview::onEnter()
{
	super::onEnter();
}

void DefensiveStanceGenericPreview::initializePositions()
{
	super::initializePositions();
}
