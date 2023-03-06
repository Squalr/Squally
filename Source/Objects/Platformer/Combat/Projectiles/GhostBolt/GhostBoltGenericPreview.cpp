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
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->previewNode->addChild(this->fireball);
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

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void GhostBoltGenericPreview::initializePositions()
{
	super::initializePositions();
}
