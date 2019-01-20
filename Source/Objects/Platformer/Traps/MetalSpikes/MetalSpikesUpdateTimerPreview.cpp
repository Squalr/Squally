#include "MetalSpikesUpdateTimerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MetalSpikesUpdateTimerPreview* MetalSpikesUpdateTimerPreview::create()
{
	MetalSpikesUpdateTimerPreview* instance = new MetalSpikesUpdateTimerPreview();

	instance->autorelease();

	return instance;
}

MetalSpikesUpdateTimerPreview::MetalSpikesUpdateTimerPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

HackablePreview* MetalSpikesUpdateTimerPreview::clone()
{
	return MetalSpikesUpdateTimerPreview::create();
}

void MetalSpikesUpdateTimerPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_MetalSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void MetalSpikesUpdateTimerPreview::initializePositions()
{
	super::initializePositions();
}
