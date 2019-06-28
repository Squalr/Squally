#include "SpeedGainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

SpeedGainGenericPreview* SpeedGainGenericPreview::create()
{
	SpeedGainGenericPreview* instance = new SpeedGainGenericPreview();

	instance->autorelease();

	return instance;
}

SpeedGainGenericPreview::SpeedGainGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

SpeedGainGenericPreview::~SpeedGainGenericPreview()
{
}

HackablePreview* SpeedGainGenericPreview::clone()
{
	return SpeedGainGenericPreview::create();
}

void SpeedGainGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void SpeedGainGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
