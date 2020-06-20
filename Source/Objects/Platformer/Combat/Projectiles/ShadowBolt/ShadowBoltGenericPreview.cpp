#include "ShadowBoltGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ShadowBoltGenericPreview* ShadowBoltGenericPreview::create()
{
	ShadowBoltGenericPreview* instance = new ShadowBoltGenericPreview();

	instance->autorelease();

	return instance;
}

ShadowBoltGenericPreview::ShadowBoltGenericPreview()
{
	this->shadowBolt = SmartAnimationSequenceNode::create(FXResources::ShadowBolt_ShadowBolt_0000);

	this->shadowBolt->setFlippedX(true);

	this->previewNode->addChild(this->shadowBolt);
}

ShadowBoltGenericPreview::~ShadowBoltGenericPreview()
{
}

HackablePreview* ShadowBoltGenericPreview::clone()
{
	return ShadowBoltGenericPreview::create();
}

void ShadowBoltGenericPreview::onEnter()
{
	super::onEnter();

	this->shadowBolt->playAnimationRepeat(FXResources::ShadowBolt_ShadowBolt_0000, 0.085f);
}

void ShadowBoltGenericPreview::initializePositions()
{
	super::initializePositions();
}
