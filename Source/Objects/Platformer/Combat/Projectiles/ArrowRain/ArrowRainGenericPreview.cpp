#include "ArrowRainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ArrowRainGenericPreview* ArrowRainGenericPreview::create()
{
	ArrowRainGenericPreview* instance = new ArrowRainGenericPreview();

	instance->autorelease();

	return instance;
}

ArrowRainGenericPreview::ArrowRainGenericPreview()
{
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->previewNode->addChild(this->fireball);
}

ArrowRainGenericPreview::~ArrowRainGenericPreview()
{
}

HackablePreview* ArrowRainGenericPreview::clone()
{
	return ArrowRainGenericPreview::create();
}

void ArrowRainGenericPreview::onEnter()
{
	super::onEnter();

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void ArrowRainGenericPreview::initializePositions()
{
	super::initializePositions();
}
