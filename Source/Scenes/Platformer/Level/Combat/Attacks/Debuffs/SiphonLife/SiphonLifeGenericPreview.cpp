#include "SiphonLifeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SiphonLifeGenericPreview* SiphonLifeGenericPreview::create()
{
	SiphonLifeGenericPreview* instance = new SiphonLifeGenericPreview();

	instance->autorelease();

	return instance;
}

SiphonLifeGenericPreview::SiphonLifeGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

SiphonLifeGenericPreview::~SiphonLifeGenericPreview()
{
}

HackablePreview* SiphonLifeGenericPreview::clone()
{
	return SiphonLifeGenericPreview::create();
}

void SiphonLifeGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void SiphonLifeGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
