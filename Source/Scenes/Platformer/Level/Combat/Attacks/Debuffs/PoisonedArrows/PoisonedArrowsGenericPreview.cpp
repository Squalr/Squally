#include "PoisonedArrowsGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

PoisonedArrowsGenericPreview* PoisonedArrowsGenericPreview::create()
{
	PoisonedArrowsGenericPreview* instance = new PoisonedArrowsGenericPreview();

	instance->autorelease();

	return instance;
}

PoisonedArrowsGenericPreview::PoisonedArrowsGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

PoisonedArrowsGenericPreview::~PoisonedArrowsGenericPreview()
{
}

HackablePreview* PoisonedArrowsGenericPreview::clone()
{
	return PoisonedArrowsGenericPreview::create();
}

void PoisonedArrowsGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void PoisonedArrowsGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
