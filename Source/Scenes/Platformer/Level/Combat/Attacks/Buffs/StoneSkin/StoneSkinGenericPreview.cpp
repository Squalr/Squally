#include "StoneSkinGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

StoneSkinGenericPreview* StoneSkinGenericPreview::create()
{
	StoneSkinGenericPreview* instance = new StoneSkinGenericPreview();

	instance->autorelease();

	return instance;
}

StoneSkinGenericPreview::StoneSkinGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

StoneSkinGenericPreview::~StoneSkinGenericPreview()
{
}

HackablePreview* StoneSkinGenericPreview::clone()
{
	return StoneSkinGenericPreview::create();
}

void StoneSkinGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void StoneSkinGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
