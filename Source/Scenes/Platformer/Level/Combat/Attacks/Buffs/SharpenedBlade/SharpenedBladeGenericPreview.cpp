#include "SharpenedBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SharpenedBladeGenericPreview* SharpenedBladeGenericPreview::create()
{
	SharpenedBladeGenericPreview* instance = new SharpenedBladeGenericPreview();

	instance->autorelease();

	return instance;
}

SharpenedBladeGenericPreview::SharpenedBladeGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

SharpenedBladeGenericPreview::~SharpenedBladeGenericPreview()
{
}

HackablePreview* SharpenedBladeGenericPreview::clone()
{
	return SharpenedBladeGenericPreview::create();
}

void SharpenedBladeGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void SharpenedBladeGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
