#include "LaserGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

LaserGenericPreview* LaserGenericPreview::create()
{
	LaserGenericPreview* instance = new LaserGenericPreview();

	instance->autorelease();

	return instance;
}

LaserGenericPreview::LaserGenericPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

HackablePreview* LaserGenericPreview::clone()
{
	return LaserGenericPreview::create();
}

void LaserGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void LaserGenericPreview::initializePositions()
{
	super::initializePositions();
}
