#include "LesserStrengthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

LesserStrengthGenericPreview* LesserStrengthGenericPreview::create()
{
	LesserStrengthGenericPreview* instance = new LesserStrengthGenericPreview();

	instance->autorelease();

	return instance;
}

LesserStrengthGenericPreview::LesserStrengthGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

LesserStrengthGenericPreview::~LesserStrengthGenericPreview()
{
}

HackablePreview* LesserStrengthGenericPreview::clone()
{
	return LesserStrengthGenericPreview::create();
}

void LesserStrengthGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void LesserStrengthGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
