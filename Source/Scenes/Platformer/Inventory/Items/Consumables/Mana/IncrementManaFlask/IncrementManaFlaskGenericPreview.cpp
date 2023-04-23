#include "IncrementManaFlaskGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

IncrementManaGenericPreview* IncrementManaGenericPreview::create()
{
	IncrementManaGenericPreview* instance = new IncrementManaGenericPreview();

	instance->autorelease();

	return instance;
}

IncrementManaGenericPreview::IncrementManaGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

IncrementManaGenericPreview::~IncrementManaGenericPreview()
{
}

HackablePreview* IncrementManaGenericPreview::clone()
{
	return IncrementManaGenericPreview::create();
}

void IncrementManaGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void IncrementManaGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
