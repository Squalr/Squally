#include "MetalSpikesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
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
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

MetalSpikesGenericPreview::~MetalSpikesGenericPreview()
{
}

HackablePreview* MetalSpikesGenericPreview::clone()
{
	return MetalSpikesGenericPreview::create();
}

void MetalSpikesGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void MetalSpikesGenericPreview::initializePositions()
{
	super::initializePositions();
}
