#include "InnerFireGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

InnerFireGenericPreview* InnerFireGenericPreview::create()
{
	InnerFireGenericPreview* instance = new InnerFireGenericPreview();

	instance->autorelease();

	return instance;
}

InnerFireGenericPreview::InnerFireGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

InnerFireGenericPreview::~InnerFireGenericPreview()
{
}

HackablePreview* InnerFireGenericPreview::clone()
{
	return InnerFireGenericPreview::create();
}

void InnerFireGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Restore_Restore_0000, 0.05f, 1.5f);
}

void InnerFireGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
