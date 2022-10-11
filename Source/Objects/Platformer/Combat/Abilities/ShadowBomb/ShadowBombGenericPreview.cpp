#include "ShadowBombGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ShadowBombGenericPreview* ShadowBombGenericPreview::create()
{
	ShadowBombGenericPreview* instance = new ShadowBombGenericPreview();

	instance->autorelease();

	return instance;
}

ShadowBombGenericPreview::ShadowBombGenericPreview()
{
	this->animationNode = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->animationNode);
}

ShadowBombGenericPreview::~ShadowBombGenericPreview()
{
}

HackablePreview* ShadowBombGenericPreview::clone()
{
	return ShadowBombGenericPreview::create();
}

void ShadowBombGenericPreview::onEnter()
{
	super::onEnter();

	this->animationNode->playAnimationRepeat(FXResources::ShadowBomb_ShadowBomb_0000, 0.05f, 0.75f, true);
}

void ShadowBombGenericPreview::initializePositions()
{
	super::initializePositions();
}
