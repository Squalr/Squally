#include "SpellOfBindingGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SpellOfBindingGenericPreview* SpellOfBindingGenericPreview::create()
{
	SpellOfBindingGenericPreview* instance = new SpellOfBindingGenericPreview();

	instance->autorelease();

	return instance;
}

SpellOfBindingGenericPreview::SpellOfBindingGenericPreview()
{
}

SpellOfBindingGenericPreview::~SpellOfBindingGenericPreview()
{
}

HackablePreview* SpellOfBindingGenericPreview::clone()
{
	return SpellOfBindingGenericPreview::create();
}

void SpellOfBindingGenericPreview::onEnter()
{
	super::onEnter();
}

void SpellOfBindingGenericPreview::initializePositions()
{
	super::initializePositions();
}
