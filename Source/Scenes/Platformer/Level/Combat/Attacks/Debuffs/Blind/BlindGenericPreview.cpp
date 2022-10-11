#include "BlindGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BlindGenericPreview* BlindGenericPreview::create()
{
	BlindGenericPreview* instance = new BlindGenericPreview();

	instance->autorelease();

	return instance;
}

BlindGenericPreview::BlindGenericPreview()
{
}

BlindGenericPreview::~BlindGenericPreview()
{
}

HackablePreview* BlindGenericPreview::clone()
{
	return BlindGenericPreview::create();
}

void BlindGenericPreview::onEnter()
{
	super::onEnter();
}

void BlindGenericPreview::initializePositions()
{
	super::initializePositions();
}
