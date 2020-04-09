#include "IncrementHealthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

IncrementHealthGenericPreview* IncrementHealthGenericPreview::create()
{
	IncrementHealthGenericPreview* instance = new IncrementHealthGenericPreview();

	instance->autorelease();

	return instance;
}

IncrementHealthGenericPreview::IncrementHealthGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

IncrementHealthGenericPreview::~IncrementHealthGenericPreview()
{
}

HackablePreview* IncrementHealthGenericPreview::clone()
{
	return IncrementHealthGenericPreview::create();
}

void IncrementHealthGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void IncrementHealthGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
