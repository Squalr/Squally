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
	this->shadowBomb = SmartAnimationSequenceNode::create(FXResources::ShadowBomb_ShadowBomb_0000);

	this->shadowBomb->setFlippedX(true);

	this->previewNode->addChild(this->shadowBomb);
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

	this->shadowBomb->playAnimationRepeat(FXResources::ShadowBomb_ShadowBomb_0000, 0.085f);
}

void ShadowBombGenericPreview::initializePositions()
{
	super::initializePositions();
}
