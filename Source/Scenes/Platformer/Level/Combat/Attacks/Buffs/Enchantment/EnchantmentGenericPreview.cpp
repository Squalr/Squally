#include "EnchantmentGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EnchantmentGenericPreview* EnchantmentGenericPreview::create()
{
	EnchantmentGenericPreview* instance = new EnchantmentGenericPreview();

	instance->autorelease();

	return instance;
}

EnchantmentGenericPreview::EnchantmentGenericPreview()
{
}

EnchantmentGenericPreview::~EnchantmentGenericPreview()
{
}

HackablePreview* EnchantmentGenericPreview::clone()
{
	return EnchantmentGenericPreview::create();
}

void EnchantmentGenericPreview::onEnter()
{
	super::onEnter();
}

void EnchantmentGenericPreview::initializePositions()
{
	super::initializePositions();
}
