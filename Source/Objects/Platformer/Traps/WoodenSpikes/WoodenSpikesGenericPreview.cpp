#include "WoodenSpikesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

WoodenSpikesGenericPreview* WoodenSpikesGenericPreview::create()
{
	WoodenSpikesGenericPreview* instance = new WoodenSpikesGenericPreview();

	instance->autorelease();

	return instance;
}

WoodenSpikesGenericPreview::WoodenSpikesGenericPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

HackablePreview* WoodenSpikesGenericPreview::clone()
{
	return WoodenSpikesGenericPreview::create();
}

void WoodenSpikesGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_MetalSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void WoodenSpikesGenericPreview::initializePositions()
{
	super::initializePositions();
}
