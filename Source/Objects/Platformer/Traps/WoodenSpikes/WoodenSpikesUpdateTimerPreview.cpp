#include "WoodenSpikesUpdateTimerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

WoodenSpikesUpdateTimerPreview* WoodenSpikesUpdateTimerPreview::create()
{
	WoodenSpikesUpdateTimerPreview* instance = new WoodenSpikesUpdateTimerPreview();

	instance->autorelease();

	return instance;
}

WoodenSpikesUpdateTimerPreview::WoodenSpikesUpdateTimerPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

HackablePreview* WoodenSpikesUpdateTimerPreview::clone()
{
	return WoodenSpikesUpdateTimerPreview::create();
}

void WoodenSpikesUpdateTimerPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void WoodenSpikesUpdateTimerPreview::initializePositions()
{
	super::initializePositions();
}
