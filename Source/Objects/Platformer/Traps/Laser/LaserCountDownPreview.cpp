#include "LaserCountDownPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

LaserCountDownPreview* LaserCountDownPreview::create()
{
	LaserCountDownPreview* instance = new LaserCountDownPreview();

	instance->autorelease();

	return instance;
}

LaserCountDownPreview::LaserCountDownPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

HackablePreview* LaserCountDownPreview::clone()
{
	return LaserCountDownPreview::create();
}

void LaserCountDownPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void LaserCountDownPreview::initializePositions()
{
	super::initializePositions();
}
