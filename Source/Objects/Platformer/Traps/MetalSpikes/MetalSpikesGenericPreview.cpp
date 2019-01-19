#include "MetalSpikesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MetalSpikesGenericPreview* MetalSpikesGenericPreview::create()
{
	MetalSpikesGenericPreview* instance = new MetalSpikesGenericPreview();

	instance->autorelease();

	return instance;
}

MetalSpikesGenericPreview::MetalSpikesGenericPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);

	this->previewSpikedLog->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikedLog);
}

HackablePreview* MetalSpikesGenericPreview::clone()
{
	return MetalSpikesGenericPreview::create();
}

void MetalSpikesGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.08f, 0.0f);
}

void MetalSpikesGenericPreview::initializePositions()
{
	super::initializePositions();
}
