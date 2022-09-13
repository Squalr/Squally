#include "RejuvinationGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RejuvinationGenericPreview* RejuvinationGenericPreview::create()
{
	RejuvinationGenericPreview* instance = new RejuvinationGenericPreview();

	instance->autorelease();

	return instance;
}

RejuvinationGenericPreview::RejuvinationGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

RejuvinationGenericPreview::~RejuvinationGenericPreview()
{
}

HackablePreview* RejuvinationGenericPreview::clone()
{
	return RejuvinationGenericPreview::create();
}

void RejuvinationGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Restore_Restore_0000, 0.05f, 1.5f);
}

void RejuvinationGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
