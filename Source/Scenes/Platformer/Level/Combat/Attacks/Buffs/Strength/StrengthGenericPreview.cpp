#include "StrengthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

StrengthGenericPreview* StrengthGenericPreview::create()
{
	StrengthGenericPreview* instance = new StrengthGenericPreview();

	instance->autorelease();

	return instance;
}

StrengthGenericPreview::StrengthGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

StrengthGenericPreview::~StrengthGenericPreview()
{
}

HackablePreview* StrengthGenericPreview::clone()
{
	return StrengthGenericPreview::create();
}

void StrengthGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void StrengthGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
