#include "GhostBoltGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

GhostBoltGenericPreview* GhostBoltGenericPreview::create()
{
	GhostBoltGenericPreview* instance = new GhostBoltGenericPreview();

	instance->autorelease();

	return instance;
}

GhostBoltGenericPreview::GhostBoltGenericPreview()
{
	this->ghostbolt = SmartAnimationSequenceNode::create(FXResources::GhostBolt_GhostBolt_0000);

	this->previewNode->addChild(this->ghostbolt);
}

GhostBoltGenericPreview::~GhostBoltGenericPreview()
{
}

HackablePreview* GhostBoltGenericPreview::clone()
{
	return GhostBoltGenericPreview::create();
}

void GhostBoltGenericPreview::onEnter()
{
	super::onEnter();

	this->ghostbolt->playAnimationRepeat(FXResources::GhostBolt_GhostBolt_0000, 0.085f);
}

void GhostBoltGenericPreview::initializePositions()
{
	super::initializePositions();
}
