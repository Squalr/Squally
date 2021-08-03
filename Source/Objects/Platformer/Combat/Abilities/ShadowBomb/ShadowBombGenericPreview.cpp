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
	this->animationNode = nullptr; // TODO

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
}

void ShadowBombGenericPreview::initializePositions()
{
	super::initializePositions();
}
