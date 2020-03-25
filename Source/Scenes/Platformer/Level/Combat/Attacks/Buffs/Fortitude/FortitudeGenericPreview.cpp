#include "FortitudeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FortitudeGenericPreview* FortitudeGenericPreview::create()
{
	FortitudeGenericPreview* instance = new FortitudeGenericPreview();

	instance->autorelease();

	return instance;
}

FortitudeGenericPreview::FortitudeGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

FortitudeGenericPreview::~FortitudeGenericPreview()
{
}

HackablePreview* FortitudeGenericPreview::clone()
{
	return FortitudeGenericPreview::create();
}

void FortitudeGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void FortitudeGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
