#include "EnchantedBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EnchantedBladeGenericPreview* EnchantedBladeGenericPreview::create()
{
	EnchantedBladeGenericPreview* instance = new EnchantedBladeGenericPreview();

	instance->autorelease();

	return instance;
}

EnchantedBladeGenericPreview::EnchantedBladeGenericPreview()
{
}

EnchantedBladeGenericPreview::~EnchantedBladeGenericPreview()
{
}

HackablePreview* EnchantedBladeGenericPreview::clone()
{
	return EnchantedBladeGenericPreview::create();
}

void EnchantedBladeGenericPreview::onEnter()
{
	super::onEnter();
}

void EnchantedBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
