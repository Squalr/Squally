#include "BloodlettingGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BloodlettingGenericPreview* BloodlettingGenericPreview::create()
{
	BloodlettingGenericPreview* instance = new BloodlettingGenericPreview();

	instance->autorelease();

	return instance;
}

BloodlettingGenericPreview::BloodlettingGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

BloodlettingGenericPreview::~BloodlettingGenericPreview()
{
}

HackablePreview* BloodlettingGenericPreview::clone()
{
	return BloodlettingGenericPreview::create();
}

void BloodlettingGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void BloodlettingGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
